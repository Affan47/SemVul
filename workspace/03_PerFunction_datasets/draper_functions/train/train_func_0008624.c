Free_INChI_Aux( INChI_Aux **ppINChI_Aux )
{
    INChI_Aux *pINChI_Aux = *ppINChI_Aux;
    if ( pINChI_Aux ) {
#if ( bREUSE_INCHI == 1 )
        if ( pINChI_Aux->nRefCount -- > 0 )
            return 1;
#endif

        qzfree( pINChI_Aux->nOrigAtNosInCanonOrd            );
        qzfree( pINChI_Aux->nIsotopicOrigAtNosInCanonOrd    );
        qzfree( pINChI_Aux->nOrigAtNosInCanonOrdInv         );
        qzfree( pINChI_Aux->nIsotopicOrigAtNosInCanonOrdInv );
        qzfree( pINChI_Aux->szOrigCoord );
        qzfree( pINChI_Aux->OrigInfo );


        qzfree( pINChI_Aux->nConstitEquNumbers                  );
        qzfree( pINChI_Aux->nConstitEquTGroupNumbers             );
        qzfree( pINChI_Aux->nConstitEquIsotopicNumbers          );
        qzfree( pINChI_Aux->nConstitEquIsotopicTGroupNumbers     );
        qzfree( pINChI_Aux );
        *ppINChI_Aux = NULL;
    }
    return 0;
}
