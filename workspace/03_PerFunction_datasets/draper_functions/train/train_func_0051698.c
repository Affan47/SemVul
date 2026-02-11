lookupGHCName( void *addr )
{
    nat i;
    for( i = 0; i < table_size && table[i].value != (StgWord) addr; ++i ) {
    }
    if (i < table_size) {
        return table[i].name;
    } else {
        return NULL;
    }
}
