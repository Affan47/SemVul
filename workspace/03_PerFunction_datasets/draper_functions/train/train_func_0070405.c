t30_set_tx_sender_ident(t30_state_t *s, const char *sender_ident)
{
    if (sender_ident == NULL)
    {
        s->tx_info.sender_ident[0] = '\0';
        return 0;
    }
    if (strlen(sender_ident) > T30_MAX_IDENT_LEN)
        return -1;
    strcpy(s->tx_info.sender_ident, sender_ident);
    return 0;
}
