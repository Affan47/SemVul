AllocateAndFillHillFormula( INChI *pINChI )
{
    int num_C, num_H, nLen, nNumNonHAtoms, ret, bOverflow;
    char *pHillFormula = NULL;
    bOverflow = 0;
    if ( !GetHillFormulaCounts( pINChI->nAtom, pINChI->nNum_H, pINChI->nNumberOfAtoms,
                          pINChI->nTautomer, pINChI->lenTautomer,
                          &num_C, &num_H, &nLen, &nNumNonHAtoms ) ) {
        if ( pHillFormula = (char*)inchi_malloc( nLen+1 ) ) {
            ret = MakeHillFormula( pINChI->nAtom+num_C, nNumNonHAtoms-num_C,
                  pHillFormula, nLen+1, num_C, num_H, &bOverflow );
            if ( ret != nLen || bOverflow ) {
                inchi_free( pHillFormula );
                pHillFormula = NULL;
            }
        }
    }
    return pHillFormula;
}
