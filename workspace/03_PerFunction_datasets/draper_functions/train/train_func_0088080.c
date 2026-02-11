find_ofchann_key_rwsocket_lockfree(int sockfd, cc_ofchannel_key_t **fd_chann_key) {

    cc_of_ret status = CC_OF_OK;
    cc_ofchannel_key_t *channel_key_tmp = NULL;
    GHashTableIter ofchannel_iter;
    cc_ofchannel_key_t *channel_key = NULL;
    cc_ofchannel_info_t *channel_info = NULL;


    g_hash_table_iter_init(&ofchannel_iter, cc_of_global.ofchannel_htbl);
    while (g_hash_table_iter_next(&ofchannel_iter,
                                  (gpointer *)&channel_key,
                                  (gpointer *)&channel_info)) {
        CC_LOG_DEBUG("%s(%d): dp/aux %lu/%hu socket %d",
                     __FUNCTION__, __LINE__, channel_key->dp_id,
                     channel_key->aux_id, channel_info->rw_sockfd);

        if (channel_info->rw_sockfd == sockfd) {
            channel_key_tmp = channel_key;
            break;
        }
    }

    if (channel_key_tmp == NULL) {
        CC_LOG_ERROR("%s(%d): could not find channel_key for rwsock %d"
                     , __FUNCTION__, __LINE__, sockfd);
        return CC_OF_EHTBL;
    }

    *fd_chann_key = channel_key_tmp;
    return status;
}
