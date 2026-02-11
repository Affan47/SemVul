rpcsvc_transport_privport_check (rpcsvc_t *svc, char *volname,
                                 rpc_transport_t *trans)
{
        union gf_sock_union     sock_union;
        int                     ret = RPCSVC_AUTH_REJECT;
        socklen_t               sinsize = sizeof (&sock_union.sin);
        char                    *srchstr = NULL;
        char                    *valstr = NULL;
        int                     globalinsecure = RPCSVC_AUTH_REJECT;
        int                     exportinsecure = RPCSVC_AUTH_DONTCARE;
        uint16_t                port = 0;
        gf_boolean_t            insecure = _gf_false;

        memset (&sock_union, 0, sizeof (sock_union));

        if ((!svc) || (!volname) || (!trans))
                return ret;

        ret = rpcsvc_transport_peeraddr (trans, NULL, 0, &sock_union.storage,
                                         sinsize);
        if (ret != 0) {
                gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to get peer addr: %s",
                        gai_strerror (ret));
                ret = RPCSVC_AUTH_REJECT;
                goto err;
        }

        port = ntohs (sock_union.sin.sin_port);
        gf_log (GF_RPCSVC, GF_LOG_TRACE, "Client port: %d", (int)port);


        if (port <= 1024) {
                ret = RPCSVC_AUTH_ACCEPT;
                goto err;
        }


        if ((dict_get (svc->options, "rpc-auth.ports.insecure"))) {
                ret = dict_get_str (svc->options, "rpc-auth.ports.insecure"
                                    , &srchstr);
                if (ret == 0) {
                        ret = gf_string2boolean (srchstr, &insecure);
                        if (ret == 0) {
                                if (insecure == _gf_true)
                                        globalinsecure = RPCSVC_AUTH_ACCEPT;
                        } else
                                gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to"
                                        " read rpc-auth.ports.insecure value");
                } else
                        gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to"
                                " read rpc-auth.ports.insecure value");
        }


        ret = gf_asprintf (&srchstr, "rpc-auth.ports.%s.insecure", volname);
        if (ret == -1) {
                gf_log (GF_RPCSVC, GF_LOG_ERROR, "asprintf failed");
                ret = RPCSVC_AUTH_REJECT;
                goto err;
        }

        if (dict_get (svc->options, srchstr)) {
                ret = dict_get_str (svc->options, srchstr, &valstr);
                if (ret == 0) {
                        ret = gf_string2boolean (valstr, &insecure);
                        if (ret == 0) {
                                if (insecure == _gf_true)
                                       exportinsecure = RPCSVC_AUTH_ACCEPT;
                                else
                                        exportinsecure = RPCSVC_AUTH_REJECT;
                        } else
                                gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to"
                                        " read rpc-auth.ports.insecure value");
                } else
                        gf_log (GF_RPCSVC, GF_LOG_ERROR, "Failed to"
                                " read rpc-auth.ports.insecure value");
        }

        ret = rpcsvc_combine_gen_spec_volume_checks (globalinsecure,
                                                         exportinsecure);
        if (ret == RPCSVC_AUTH_ACCEPT)
                gf_log (GF_RPCSVC, GF_LOG_DEBUG, "Unprivileged port allowed");
        else
                gf_log (GF_RPCSVC, GF_LOG_DEBUG, "Unprivileged port not"
                        " allowed");

err:
        GF_FREE (srchstr);

        return ret;
}
