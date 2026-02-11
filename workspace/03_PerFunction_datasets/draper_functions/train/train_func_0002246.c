__socket_reset_priv (socket_private_t *priv)
{
        struct gf_sock_incoming      *in         = NULL;


        in = &priv->incoming;

        if (in->iobref) {
                iobref_unref (in->iobref);
                in->iobref = NULL;
        }

        if (in->iobuf) {
                iobuf_unref (in->iobuf);
        }

        if (in->request_info != NULL) {
                GF_FREE (in->request_info);
                in->request_info = NULL;
        }

        memset (&in->payload_vector, 0,
                sizeof (in->payload_vector));

        in->iobuf = NULL;
}
