cc_of_lib_init(of_dev_type_e dev_type)
{
    cc_of_ret status = CC_OF_OK;
    CC_LOG_INFO("%s(%d): %s", __FUNCTION__, __LINE__,
                "CC_OF_LIB Started Initializing");


    cc_of_global.ofdebug_enable = FALSE;
    cc_of_global.oflog_enable = FALSE;
    cc_of_global.ofut_enable = FALSE;
    cc_of_global.oflog_fd = NULL;
    cc_of_global.oflog_file = malloc(sizeof(char) *
                                     LOG_FILE_NAME_SIZE);
    g_mutex_init(&cc_of_global.oflog_lock);

    cc_of_global.ofdev_type = dev_type;
    cc_of_global.ofdev_htbl = g_hash_table_new_full(cc_ofdev_hash_func,
                                                    cc_ofdev_htbl_equal_func, NULL, NULL);


    if (cc_of_global.ofdev_htbl == NULL) {
	    status = CC_OF_EHTBL;
	    cc_of_lib_free();

	    CC_LOG_FATAL("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
    }
    g_mutex_init(&cc_of_global.ofdev_htbl_lock);

    cc_of_global.ofchannel_htbl = g_hash_table_new_full(cc_ofchann_hash_func,
                                                        cc_ofchannel_htbl_equal_func,
                                                        cc_of_destroy_generic,
                                                        cc_of_destroy_generic);
    if (cc_of_global.ofchannel_htbl == NULL) {
	    status = CC_OF_EHTBL;
	    cc_of_lib_free();
	    CC_LOG_FATAL("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
    }
    g_mutex_init(&cc_of_global.ofchannel_htbl_lock);

    cc_of_global.ofrw_htbl = g_hash_table_new_full(cc_ofrw_hash_func,
                                                   cc_ofrw_htbl_equal_func,
                                                   cc_of_destroy_generic,
                                                   cc_of_destroy_generic);

    if (cc_of_global.ofrw_htbl == NULL) {
	    status = CC_OF_EHTBL;
	    cc_of_lib_free();
	    CC_LOG_FATAL("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
    }
    g_mutex_init(&cc_of_global.ofrw_htbl_lock);

    cc_of_global.NET_SVCS[TCP] = tcp_sockfns;
    cc_of_global.NET_SVCS[UDP] = udp_sockfns;

    cc_of_global.oflisten_pollthr_p = adp_thr_mgr_new("oflisten_thr",
                                                      MAX_PER_THREAD_RWSOCKETS,
                                                      MAX_PER_THREAD_PIPES);
    if (cc_of_global.oflisten_pollthr_p == NULL) {
	    status = CC_OF_EMISC;
	    cc_of_lib_free();
	    CC_LOG_FATAL("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
    }
    CC_LOG_DEBUG("%s(%d): %s", __FUNCTION__, __LINE__,
                 "CREATED POLLTHR FOR listen sockets");

    cc_of_global.ofrw_pollthr_list = NULL;
    g_mutex_init(&cc_of_global.ofrw_pollthr_list_lock);
    adpoll_thread_mgr_t *tmgr = NULL;
    if ((status = cc_create_rw_pollthr_safe(&tmgr)) < 0) {
	    cc_of_lib_free();
	    CC_LOG_FATAL("%s(%d): %s", __FUNCTION__, __LINE__,
                     cc_of_strerror(status));
    }
    CC_LOG_DEBUG("%s(%d): %s", __FUNCTION__, __LINE__,
                 "CREATED POLLTHR FOR rwsockets");
    CC_LOG_INFO("%s(%d): %s", __FUNCTION__, __LINE__,
                "CC_OF_LIB initilaized successfully");
    return status;
}
