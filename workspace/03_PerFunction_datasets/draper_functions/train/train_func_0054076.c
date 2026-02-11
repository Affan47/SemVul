new_connection(void)
{
    CONNECTION *c = CALLOC(1, sizeof(CONNECTION));

    if(!c)
    {
        OUTOFMEMORY("new_connection");
        return 0;
    }
#ifdef ONAP_DEBUG
    c->magic = MAGIC_CONNECTION;
#endif
    return c;
}
