vnc_connection_flush(VncConnection *conn)
{
    VncConnectionPrivate *priv = conn->priv;


#ifdef HAVE_SASL
    if (priv->saslconn)
        vnc_connection_flush_sasl(conn);
    else
#endif
        vnc_connection_flush_plain(conn);
    priv->write_offset = 0;
}
