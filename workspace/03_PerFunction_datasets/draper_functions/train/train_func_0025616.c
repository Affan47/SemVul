sock_write(Socket * s, gchar * str)
{
    while (!sock_ready_to_write(s));

    return write(s->sock, str, strlen(str));
}
