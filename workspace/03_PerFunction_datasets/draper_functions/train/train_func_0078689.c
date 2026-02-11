globus_fifo_destroy ( globus_fifo_t * fifo)
{
    struct globus_fifo_s * s_fifo;

    if (fifo == GLOBUS_NULL)
    {
        return;
    }

    s_fifo = *fifo;
    globus_list_free (s_fifo->head);
    s_fifo->head = GLOBUS_NULL;
    s_fifo->tail = GLOBUS_NULL;
    s_fifo->size = 0;

    globus_free(s_fifo);
}
