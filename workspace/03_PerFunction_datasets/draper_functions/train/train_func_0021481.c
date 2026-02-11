syck_hdlr_add_anchor( SyckParser *p, char *a, SyckNode *n )
{
    SyckNode *ntmp = NULL;

    n->anchor = a;
    if ( p->bad_anchors != NULL )
    {
        SyckNode *bad;
        if ( st_lookup( p->bad_anchors, (st_data_t)a, (void *)&bad ) )
        {
            if ( n->kind != syck_str_kind )
            {
                n->id = bad->id;
                (p->handler)( p, n );
            }
        }
    }
    if ( p->anchors == NULL )
    {
        p->anchors = st_init_strtable();
    }
    if ( st_lookup( p->anchors, (st_data_t)a, (void *)&ntmp ) )
    {
        if ( ntmp != (void *)1 )
        {
            syck_free_node( ntmp );
        }
    }
    st_insert( p->anchors, (st_data_t)a, (st_data_t)n );
    return n;
}
