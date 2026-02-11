FreeAllINChIArrays( PINChI2 *pINChI[INCHI_NUM], PINChI_Aux2 *pINChI_Aux[INCHI_NUM], int num_components[INCHI_NUM] )
{
    int k;
    for ( k = 0; k < INCHI_NUM; k ++ ) {
        FreeINChIArrays( pINChI[k], pINChI_Aux[k], num_components[k] );
        num_components[k] = 0;
        if ( pINChI[k] ) {
            inchi_free( pINChI[k] );
            pINChI[k] = NULL;
        }
        if ( pINChI_Aux[k] ) {
            inchi_free( pINChI_Aux[k] );
            pINChI_Aux[k] = NULL;
        }

    }
}
