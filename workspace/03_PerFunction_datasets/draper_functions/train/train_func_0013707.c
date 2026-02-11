orte_oob_tcp_start_listening(void)
{
    int rc;
    mca_oob_tcp_listener_t *listener;


    if (NULL == mca_oob_tcp_component.ipv4conns
#if OPAL_ENABLE_IPV6
        && NULL == mca_oob_tcp_component.ipv6conns
#endif
        ) {
        ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
        return ORTE_ERR_NOT_FOUND;
    }


    if (ORTE_SUCCESS != (rc = create_listen())) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }

#if OPAL_ENABLE_IPV6

    if (ORTE_SUCCESS != (rc = create_listen6())) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }
#endif


    if (ORTE_PROC_IS_HNP) {
        mca_oob_tcp_component.listen_thread_active = true;
        mca_oob_tcp_component.listen_thread.t_run = listen_thread;
        mca_oob_tcp_component.listen_thread.t_arg = NULL;
        if (OPAL_SUCCESS != (rc = opal_thread_start(&mca_oob_tcp_component.listen_thread))) {
            ORTE_ERROR_LOG(rc);
            opal_output(0, "%s Unable to start listen thread", ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
        }
        return rc;
    }


    OPAL_LIST_FOREACH(listener, &mca_oob_tcp_component.listeners, mca_oob_tcp_listener_t) {
        listener->ev_active = true;
        opal_event_set(orte_event_base, &listener->event,
                       listener->sd,
                       OPAL_EV_READ|OPAL_EV_PERSIST,
                       connection_event_handler,
                       0);
        opal_event_set_priority(&listener->event, ORTE_MSG_PRI);
        opal_event_add(&listener->event, 0);
    }

    return ORTE_SUCCESS;
}
