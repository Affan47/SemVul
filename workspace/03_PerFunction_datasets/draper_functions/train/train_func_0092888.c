fli_extend_event_queue( void )
{
    FL_EVENT_QUEUE_ENTRY *p = fl_malloc( ( FLI_QSIZE + 1 ) * sizeof *p );
    size_t i;


    p->next = event_queue.blocks;
    event_queue.blocks = p++;


    event_queue.empty = p;

    for ( i = 0; i < FLI_QSIZE - 1; p++, i++ )
        p->next = p + 1;

    p->next = NULL;
}
