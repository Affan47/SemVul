Alloc_INChI_Aux( int num_at, int num_isotopic_atoms, int nAllocMode, int bOrigCoord )
{
    INChI_Aux     *pINChI_Aux;
    int    bIsotopic   = (nAllocMode & REQ_MODE_ISO);
    int    num_at_tg   = num_at + num_at/2;


    if ( num_at <= 0 || NULL == (pINChI_Aux = (INChI_Aux *)inchi_calloc(sizeof(INChI_Aux), 1))) {
        return NULL;
    }
    if ( (pINChI_Aux->nOrigAtNosInCanonOrd      = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nOrigAtNosInCanonOrd[0]), num_at_tg)) &&
         (pINChI_Aux->nOrigAtNosInCanonOrdInv   = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nOrigAtNosInCanonOrd[0]), num_at_tg)) &&
         (pINChI_Aux->nConstitEquNumbers        = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nConstitEquNumbers[0]), num_at_tg)) ) {
        ;
    } else {
        goto out_of_RAM;
    }

    if ( num_at > 1 &&
         (pINChI_Aux->nConstitEquTGroupNumbers  = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nConstitEquTGroupNumbers[0]), num_at/2+1)) ) {
        ;
    } else
    if ( num_at > 1 ) {
        goto out_of_RAM;
    }

    if ( num_at > 0 ) {
        pINChI_Aux->OrigInfo    = (ORIG_INFO *)inchi_calloc(sizeof(pINChI_Aux->OrigInfo[0]), num_at);
        if ( !pINChI_Aux->OrigInfo )
            goto out_of_RAM;
    }
    if ( bOrigCoord && num_at > 0 ) {
        pINChI_Aux->szOrigCoord = (MOL_COORD *)inchi_calloc(sizeof(pINChI_Aux->szOrigCoord[0]), num_at);
        if ( !pINChI_Aux->szOrigCoord )
            goto out_of_RAM;
    }
    if ( bIsotopic ) {
        if (
             (pINChI_Aux->nIsotopicOrigAtNosInCanonOrd    = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nIsotopicOrigAtNosInCanonOrd[0]), num_at_tg)) &&
             (pINChI_Aux->nIsotopicOrigAtNosInCanonOrdInv = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nIsotopicOrigAtNosInCanonOrd[0]), num_at_tg)) &&
             (pINChI_Aux->nConstitEquIsotopicNumbers      = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nConstitEquIsotopicNumbers[0]), num_at_tg)) ) {
            ;
        } else
        if ( num_isotopic_atoms ) {
            goto out_of_RAM;
        }
        if (
             (pINChI_Aux->nConstitEquIsotopicTGroupNumbers = (AT_NUMB*)inchi_calloc(sizeof(pINChI_Aux->nConstitEquIsotopicTGroupNumbers[0]), num_at/2+1)) ) {
            ;
        } else
        if ( num_isotopic_atoms && num_at > 1 ) {
            goto out_of_RAM;
        }
    }
    return pINChI_Aux;


out_of_RAM:
    if ( pINChI_Aux ) {
        Free_INChI_Aux(&pINChI_Aux);


    }
    return NULL;
}
