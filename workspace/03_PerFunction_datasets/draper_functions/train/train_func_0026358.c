t30_get_rx_nss(t30_state_t *s, const uint8_t *nss[])
{
    if (nss)
        *nss = s->rx_info.nss;
    return s->rx_info.nss_len;
}
