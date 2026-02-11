vnc_connection_flush_sasl(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;
    const char *output;
    unsigned int outputlen;
    int err;

    err = sasl_encode(priv->saslconn,
                      priv->write_buffer,
                      priv->write_offset,
                      &output, &outputlen);
    if (err != SASL_OK) {
        VNC_DEBUG("Failed to encode SASL data %s",
                  sasl_errstring(err, NULL, NULL));
        priv->has_error = TRUE;
        return;
    }

    vnc_connection_flush_wire(conn, output, outputlen);
}
