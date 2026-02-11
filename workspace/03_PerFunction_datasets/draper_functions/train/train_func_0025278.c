__socket_reset (rpc_transport_t *this)
{
        socket_private_t *priv = NULL;

        GF_VALIDATE_OR_GOTO ("socket", this, out);
        GF_VALIDATE_OR_GOTO ("socket", this->private, out);

        priv = this->private;


        if (priv->incoming.iobref) {
                iobref_unref (priv->incoming.iobref);
                priv->incoming.iobref = NULL;
        }

        if (priv->incoming.iobuf) {
                iobuf_unref (priv->incoming.iobuf);
        }

        if (priv->incoming.request_info != NULL) {
                GF_FREE (priv->incoming.request_info);
        }

        memset (&priv->incoming, 0, sizeof (priv->incoming));

        event_unregister (this->ctx->event_pool, priv->sock, priv->idx);

        close (priv->sock);
        priv->sock = -1;
        priv->idx = -1;
        priv->connected = -1;

out:
        return;
}
