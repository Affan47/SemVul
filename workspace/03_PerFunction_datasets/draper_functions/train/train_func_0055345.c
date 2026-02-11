NodeSetCreate( NodeSet *pSet, int n, int L )
{
    int i, len;

    len = (n+ num_bit - 1)/num_bit;

    pSet->bitword = (bitWord**)inchi_calloc(L, sizeof(pSet->bitword[0]));

    if ( !pSet->bitword ) {
        return 0;
    }
    pSet->bitword[0] = (bitWord*)inchi_calloc(len*L, sizeof(pSet->bitword[0][0]));
    if ( !pSet->bitword[0] ) {

        inchi_free( pSet->bitword );
        pSet->bitword = NULL;
        return 0;
    }
    for ( i = 1; i < L; i ++ ) {
        pSet->bitword[i] = pSet->bitword[i-1]+len;
    }
    pSet->len_set = len;
    pSet->num_set = L;
    return 1;
}
