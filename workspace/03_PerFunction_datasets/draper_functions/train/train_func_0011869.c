vnc_connection_read_zrle_pi(VncConnection *conn, int palette_size)
{
    VncConnectionPrivate *priv = conn->priv;
    guint8 pi = 0;

    if (priv->zrle_pi_bits == 0) {
        priv->zrle_pi = vnc_connection_read_u8(conn);
        priv->zrle_pi_bits = 8;
    }
    if ( palette_size == 2) {
        pi = (priv->zrle_pi >> (priv->zrle_pi_bits - 1)) & 1;
        priv->zrle_pi_bits -= 1;
    } else if ((palette_size == 3) || (palette_size == 4)) {
        pi = (priv->zrle_pi >> (priv->zrle_pi_bits - 2)) & 3;
        priv->zrle_pi_bits -= 2;
    } else if ((palette_size >=5) && (palette_size <=16)){
        pi = (priv->zrle_pi >> (priv->zrle_pi_bits - 4)) & 15;
        priv->zrle_pi_bits -= 4;
    }

    return pi;
}
