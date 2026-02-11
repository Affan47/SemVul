SortedEquInfoToRanks( const AT_RANK* nSymmRank, AT_RANK* nRank, const AT_RANK* nAtomNumber, int num_atoms, int *bChanged )
{
    AT_RANK        rNew, rOld, nNumDiffRanks;
    int            i, j, nNumChanges = 0;
    for ( i = num_atoms-1, j = (int)nAtomNumber[i],
          rOld = nSymmRank[j], rNew = nRank[j] = (AT_RANK)num_atoms,
          nNumDiffRanks = 1;
             i > 0;
                 i -- ) {

        j = (int)nAtomNumber[i-1];

        if ( nSymmRank[j] != rOld ) {
            nNumDiffRanks ++;
            rNew = (AT_RANK)i;
            nNumChanges += (rOld != rNew+1);
            rOld = nSymmRank[j];
        }

        nRank[j] = rNew;
    }
    if ( bChanged ) {
        *bChanged = (0 != nNumChanges);
    }
    return nNumDiffRanks;
}
