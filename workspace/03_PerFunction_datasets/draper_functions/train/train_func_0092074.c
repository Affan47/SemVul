socket_proto_state_machine (rpc_transport_t *this,
                            rpc_transport_pollin_t **pollin)
{
        socket_private_t *priv = NULL;
        int               ret = 0;

        GF_VALIDATE_OR_GOTO ("socket", this, out);
        GF_VALIDATE_OR_GOTO ("socket", this->private, out);

        priv = this->private;

        pthread_mutex_lock (&priv->lock);
        {
                ret = __socket_proto_state_machine (this, pollin);
        }
        pthread_mutex_unlock (&priv->lock);

out:
        return ret;
}
