CountNextCycle( const RefLinkedBase * pThis )
{
    if ( NULL == pThis )
        return 0;
    const RefLinkedBase * p = pThis->next_;
    if ( NULL == p )
        return 0;
    if ( pThis == p )
        return 1;

    unsigned int count = 1;
    while ( p != pThis )
    {
        p = p->next_;
        ++count;
    }

    return count;
}
