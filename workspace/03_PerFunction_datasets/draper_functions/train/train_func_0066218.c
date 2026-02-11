alloc_node(void)
{
    KBNODE n;

    n = unused_nodes;
    if( n )
	unused_nodes = n->next;
    else
	n = xmalloc( sizeof *n );
    n->next = NULL;
    n->pkt = NULL;
    n->flag = 0;
    n->private_flag=0;
    n->recno = 0;
    return n;
}
