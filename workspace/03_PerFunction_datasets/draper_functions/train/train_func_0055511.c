add_hash( Map* m )
    {
    unsigned int h, he, i;

    h = hash( m->ino, m->dev, m->size, m->ctime );
    he = ( h + hash_size - 1 ) & hash_mask;
    for ( i = h; ; i = ( i + 1 ) & hash_mask )
    {
    if ( hash_table[i] == (Map*) 0 )
        {
        hash_table[i] = m;
        m->hash = h;
        m->hash_idx = i;
        return 0;
        }
    if ( i == he )
        break;
    }
    return -1;
    }
