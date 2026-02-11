cc_add_sockfd_rw_pollthr_safe(adpoll_thr_msg_t *thr_msg,
                              cc_ofdev_key_t key,
                              L4_type_e layer4_proto,
                              cc_ofchannel_key_t ofchann_key)
{
    cc_of_ret status = CC_OF_OK;
    adpoll_thread_mgr_t *tmgr = NULL;


    status = cc_find_or_create_rw_pollthr_safe(&tmgr);

    if(status < 0) {
        CC_LOG_ERROR("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
        return status;
    } else {


        g_mutex_lock(&cc_of_global.ofdev_htbl_lock);
        g_mutex_lock(&cc_of_global.ofchannel_htbl_lock);
        g_mutex_lock(&cc_of_global.ofrw_htbl_lock);


        CC_LOG_DEBUG("%s(%d) dev controller ip 0x%x, switch ip 0x%x, "
                     "layer4 port %d", __FUNCTION__, __LINE__,
                     key.controller_ip_addr, key.switch_ip_addr,
                     key.controller_L4_port);

        status = atomic_add_upd_htbls_with_rwsocket_lockfree(
            thr_msg->fd, NULL,
            tmgr,
            key,
            layer4_proto,
            ofchann_key);

        g_mutex_unlock(&cc_of_global.ofrw_htbl_lock);
        g_mutex_unlock(&cc_of_global.ofchannel_htbl_lock);
        g_mutex_unlock(&cc_of_global.ofdev_htbl_lock);

        if (status < 0) {
            CC_LOG_ERROR("%s(%d): %s", __FUNCTION__, __LINE__,
                         cc_of_strerror(status));

            g_mutex_lock(&cc_of_global.ofdev_htbl_lock);
            g_mutex_lock(&cc_of_global.ofchannel_htbl_lock);
            g_mutex_lock(&cc_of_global.ofrw_htbl_lock);

            cc_del_sockfd_rw_pollthr_lockfree(tmgr, thr_msg);

            g_mutex_unlock(&cc_of_global.ofrw_htbl_lock);
            g_mutex_unlock(&cc_of_global.ofchannel_htbl_lock);
            g_mutex_unlock(&cc_of_global.ofdev_htbl_lock);

            return status;
        }

        CC_LOG_DEBUG("%s(%d): adding fd %d to thread %s",
                     __FUNCTION__, __LINE__, thr_msg->fd,
                     tmgr->tname);
        CC_LOG_DEBUG("%s(%d): succesfully added fd %d to thread",
                     __FUNCTION__, __LINE__, thr_msg->fd);
        adp_thr_mgr_add_del_fd(tmgr, thr_msg);
    }

    return status;
}
