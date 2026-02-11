wasp_mq_recv( wasp_mq q, void** data ){
    wasp_message m = q->first;
    wasp_message n;

    if( ! m ){
        return 0;
    };

    n = m->next;

    if( n ){
        q->first = n;
    }else{
        q->first = q->last = NULL;
    }

    if( data ) *data = m->content;
    free( m );

    return 1;
}
