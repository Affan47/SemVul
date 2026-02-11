notify (xlator_t *this, int32_t event, void *data, ...)
{
        clnt_conf_t     *conf  = NULL;

        conf = this->private;
        if (!conf)
                return 0;

        switch (event) {
        case GF_EVENT_PARENT_UP:
        {
                gf_log (this->name, GF_LOG_INFO,
                        "parent translators are ready, attempting connect "
                        "on transport");

                rpc_clnt_start (conf->rpc);
                break;
        }

        case GF_EVENT_PARENT_DOWN:
                gf_log (this->name, GF_LOG_INFO,
                        "current graph is no longer active, destroying "
                        "rpc_client ");

                pthread_mutex_lock (&conf->lock);
                {
                        conf->parent_down = 1;
                }
                pthread_mutex_unlock (&conf->lock);

                rpc_clnt_disable (conf->rpc);
                break;

        default:
                gf_log (this->name, GF_LOG_DEBUG,
                        "got %d, calling default_notify ()", event);

                default_notify (this, event, data);
                conf->last_sent_event = event;
                break;
        }

        return 0;
}
