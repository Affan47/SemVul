JANUS_Shutdown(void)
{
    uint8_t i;

    for (i = 0; i < 2; ++i)
        queue_free(mitm_desc[i].pqueue);

    pbufs_free(pbufs);

    free(macpkt);
}
