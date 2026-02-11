soap_server_stop(PrivData* privdata)
{


    debug("bb.soap.server_stop",0,"SOAP[%s]: Stopping HTTP server", octstr_get_cstr(privdata->name));

    privdata->soap_server = 0;


    http_close_port(privdata->port);

    if (privdata->server_thread) {
        gwthread_wakeup(privdata->server_thread);
        gwthread_join(privdata->server_thread);
        privdata->server_thread = 0;
    }


    debug("bb.soap.server_stop",0,"SOAP[%s]: Done stopping HTTP server", octstr_get_cstr(privdata->name));
}
