start_epoll(int port, EpollSocketWatcher &socket_handler, int backlog, int max_events) {
    _backlog = backlog;
    _port = port;

    if (_thread_pool == NULL) {
        int core_size = get_nprocs();
        LOG_INFO("thread pool not set, we will build for core size:%d", core_size);
        _thread_pool = new ThreadPool();
        _thread_pool->set_pool_size(core_size);
    }
    int ret = _thread_pool->start();
    if (ret != 0) {
        LOG_ERROR("thread pool start error:%d", ret);
        return ret;
    }
    ret = this->listen_on();
    if (ret != 0) {
        return ret;
    }


    int epollfd = epoll_create(1024);
    if (epollfd == -1) {
        LOG_ERROR("epoll_create:%s", strerror(errno));
        return -1;
    }

    for (std::set<int>::iterator i = _listen_sockets.begin(); i != _listen_sockets.end(); i++) {
        int sockfd = *i;
        struct epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = sockfd;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
            LOG_ERROR("epoll_ctl: listen_sock:%s", strerror(errno));
            return -1;
        }
    }

    epoll_event *events = new epoll_event[max_events];
    while (1) {
        int fds_num = epoll_wait(epollfd, events, max_events, -1);
        if (fds_num == -1) {
            if (errno == EINTR) {
                continue;
            }
            LOG_ERROR("epoll_pwait:%s", strerror(errno));
            break;
        }

        for (int i = 0; i < fds_num; i++) {
            if(_listen_sockets.count(events[i].data.fd)) {

                this->handle_accept_event(epollfd, events[i], socket_handler);
            } else if(events[i].events & EPOLLIN ){

                this->handle_readable_event(epollfd, events[i], socket_handler);
            } else if(events[i].events & EPOLLOUT) {

                this->handle_writeable_event(epollfd, events[i], socket_handler);
            } else {
                LOG_INFO("unkonw events :%d", events[i].events);
            }
        }
    }
    if (events != NULL) {
        delete[] events;
        events = NULL;
    }
    return -1;
}
