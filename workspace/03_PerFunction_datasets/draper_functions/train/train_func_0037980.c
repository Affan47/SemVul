start_unicast_message(struct neighbour *neigh, int type, int len)
{
    if(unicast_neighbour) {
        if(neigh != unicast_neighbour ||
           unicast_buffered + len + 2 >=
           MIN(UNICAST_BUFSIZE, neigh->ifp->bufsize))
            flush_unicast(0);
    }
    if(!unicast_buffer)
        unicast_buffer = malloc(UNICAST_BUFSIZE);
    if(!unicast_buffer) {
        perror("malloc(unicast_buffer)");
        return -1;
    }

    unicast_neighbour = neigh;

    unicast_buffer[unicast_buffered++] = type;
    unicast_buffer[unicast_buffered++] = len;
    return 1;
}
