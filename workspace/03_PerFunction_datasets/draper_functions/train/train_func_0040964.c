bRevInchiComponentExists( StrFromINChI *pStruct, int iInChI, int bMobileH, int k )
{
    if ( !pStruct ||  !pStruct->num_atoms ||
         INCHI_BAS != iInChI   && iInChI != INCHI_REC  ||
         TAUT_NON  != bMobileH && TAUT_YES != bMobileH || k < 0 ) {
        return 0;
    }
    return ( k < pStruct->RevInChI.num_components[iInChI] &&
                 pStruct->RevInChI.pINChI[iInChI] &&
                 pStruct->RevInChI.pINChI[iInChI][k][bMobileH] &&
                 pStruct->RevInChI.pINChI[iInChI][k][bMobileH]->nNumberOfAtoms > 0 &&
                !pStruct->RevInChI.pINChI[iInChI][k][bMobileH]->bDeleted );
}
