aisc_close(aisc_com * link)
{
    if (link) {
        if (link->socket) {
            link->aisc_mes_buffer[0] = 0;
            link->aisc_mes_buffer[1] = 0;
            link->aisc_mes_buffer[2] = 0;
            aisc_c_write(link->socket, (char *)(link->aisc_mes_buffer), 3 * sizeof(long));
            shutdown(link->socket, 2);
            close(link->socket);
            link->socket = 0;
        }
        free((char *)link);
    }
    return 0;
}
