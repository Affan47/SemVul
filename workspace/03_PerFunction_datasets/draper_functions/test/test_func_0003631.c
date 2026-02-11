xhash_zapx(xht h, const char *key, int len)
{
    xhn n;
    int index;

    if( !h || !key ) return;

    index = _xhasher(key,len);
    n = _xhash_node_get(h, key, len, index);
    if( !n ) return;


    xhash_zap_inner(h ,n, index );
}
