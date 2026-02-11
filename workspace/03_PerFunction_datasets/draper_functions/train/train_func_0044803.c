event_register_epoll (struct event_pool *event_pool, int fd,
                      event_handler_t handler,
                      void *data, int poll_in, int poll_out)
{
        int                 idx = -1;
        int                 ret = -1;
        struct epoll_event  epoll_event = {0, };
        struct event_data  *ev_data = (void *)&epoll_event.data;


        GF_VALIDATE_OR_GOTO ("event", event_pool, out);

        pthread_mutex_lock (&event_pool->mutex);
        {
                if (event_pool->count == event_pool->used) {
                        event_pool->count *= 2;

                        event_pool->reg = GF_REALLOC (event_pool->reg,
                                                      event_pool->count *
                                                      sizeof (*event_pool->reg));

                        if (!event_pool->reg) {
                                gf_log ("epoll", GF_LOG_ERROR,
                                        "event registry re-allocation failed");
                                goto unlock;
                        }
                }

                idx = event_pool->used;
                event_pool->used++;

                event_pool->reg[idx].fd = fd;
                event_pool->reg[idx].events = EPOLLPRI;
                event_pool->reg[idx].handler = handler;
                event_pool->reg[idx].data = data;

                switch (poll_in) {
                case 1:
                        event_pool->reg[idx].events |= EPOLLIN;
                        break;
                case 0:
                        event_pool->reg[idx].events &= ~EPOLLIN;
                        break;
                case -1:

                        break;
                default:
                        gf_log ("epoll", GF_LOG_ERROR,
                                "invalid poll_in value %d", poll_in);
                        break;
                }

                switch (poll_out) {
                case 1:
                        event_pool->reg[idx].events |= EPOLLOUT;
                        break;
                case 0:
                        event_pool->reg[idx].events &= ~EPOLLOUT;
                        break;
                case -1:

                        break;
                default:
                        gf_log ("epoll", GF_LOG_ERROR,
                                "invalid poll_out value %d", poll_out);
                        break;
                }

                event_pool->changed = 1;

                epoll_event.events = event_pool->reg[idx].events;
                ev_data->fd = fd;
                ev_data->idx = idx;

                ret = epoll_ctl (event_pool->fd, EPOLL_CTL_ADD, fd,
                                 &epoll_event);

                if (ret == -1) {
                        gf_log ("epoll", GF_LOG_ERROR,
                                "failed to add fd(=%d) to epoll fd(=%d) (%s)",
                                fd, event_pool->fd, strerror (errno));
                        goto unlock;
                }

                pthread_cond_broadcast (&event_pool->cond);
        }
unlock:
        pthread_mutex_unlock (&event_pool->mutex);

out:
        return ret;
}
