fini (struct rpc_transport *this)
{

        gf_rdma_private_t *priv = NULL;

        priv = this->private;

        this->private = NULL;

        if (priv) {
                pthread_mutex_destroy (&priv->recv_mutex);
                pthread_mutex_destroy (&priv->write_mutex);
                pthread_mutex_destroy (&priv->read_mutex);


                if (priv->sock != -1) {
                        event_unregister (this->ctx->event_pool,
                                          priv->sock, priv->idx);
                }

                gf_log (this->name, GF_LOG_TRACE,
                        "called fini on transport: %p", this);
                GF_FREE (priv);
        }
        return;
}
