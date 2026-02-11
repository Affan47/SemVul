glusterd_shd_rpc_notify (struct rpc_clnt *rpc, void *mydata,
                         rpc_clnt_event_t event,
                         void *data)
{
        xlator_t                *this = NULL;
        glusterd_conf_t         *conf = NULL;
        int                     ret = 0;

        this = THIS;
        GF_ASSERT (this);
        conf = this->private;
        GF_ASSERT (conf);

        switch (event) {
        case RPC_CLNT_CONNECT:
                gf_log (this->name, GF_LOG_DEBUG, "got RPC_CLNT_CONNECT");
                (void) glusterd_shd_set_running (_gf_true);
                ret = default_notify (this, GF_EVENT_CHILD_UP, NULL);

                break;

        case RPC_CLNT_DISCONNECT:
                gf_log (this->name, GF_LOG_DEBUG, "got RPC_CLNT_DISCONNECT");
                (void) glusterd_shd_set_running (_gf_false);
                break;

        default:
                gf_log (this->name, GF_LOG_TRACE,
                        "got some other RPC event %d", event);
                break;
        }

        return ret;
}
