gf_server_check_getxattr_cmd (call_frame_t *frame, const char *key)
{

        server_conf_t    *conf = NULL;
        rpc_transport_t  *xprt = NULL;

        conf = frame->this->private;
        if (!conf)
                return 0;

        if (fnmatch ("*list*mount*point*", key, 0) == 0) {

                list_for_each_entry (xprt, &conf->xprt_list, list) {
                        gf_log ("mount-point-list", GF_LOG_INFO,
                                "%s", xprt->peerinfo.identifier);
                }
        }


        return 0;
}
