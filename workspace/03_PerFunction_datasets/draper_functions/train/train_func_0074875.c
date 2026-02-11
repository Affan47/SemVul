mud_telnet_set_telopt_queue(guchar *storage, gint bit_on, const guint bitshift)
{
    *storage = bit_on ? (*storage | (0x04u << bitshift)) : (*storage & ~(0x04u << bitshift));
}
