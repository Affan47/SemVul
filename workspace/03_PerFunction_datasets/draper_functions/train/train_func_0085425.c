ClpCholeskyCtriRec(ClpCholeskyDenseC * thisStruct, longDouble * aTri, int nThis, longDouble * aUnder,
                   longDouble * diagonal, longDouble * work,
                   int nLeft, int iBlock, int jBlock,
                   int numberBlocks)
{
     if (nThis <= BLOCK && nLeft <= BLOCK) {
          ClpCholeskyCtriRecLeaf( aTri, aUnder, diagonal, work, nLeft);
     } else if (nThis < nLeft) {
          int nb = number_blocks((nLeft + 1) >> 1);
          int nLeft2 = number_rows(nb);
          cilk_spawn ClpCholeskyCtriRec(thisStruct, aTri, nThis, aUnder, diagonal, work, nLeft2, iBlock, jBlock, numberBlocks);
          ClpCholeskyCtriRec(thisStruct, aTri, nThis, aUnder + number_entries(nb), diagonal, work, nLeft - nLeft2,
                             iBlock + nb, jBlock, numberBlocks);
	  cilk_sync;
     } else {
          int nb = number_blocks((nThis + 1) >> 1);
          int nThis2 = number_rows(nb);
          longDouble * aother;
          int kBlock = jBlock + nb;
          int i;
          int nintri = (nb * (nb + 1)) >> 1;
          int nbelow = (numberBlocks - nb) * nb;
          ClpCholeskyCtriRec(thisStruct, aTri, nThis2, aUnder, diagonal, work, nLeft, iBlock, jBlock, numberBlocks);

          i = ((numberBlocks - jBlock) * (numberBlocks - jBlock - 1) -
               (numberBlocks - jBlock - nb) * (numberBlocks - jBlock - nb - 1)) >> 1;
          aother = aUnder + number_entries(i);
          ClpCholeskyCrecRec(thisStruct, aTri + number_entries(nb), nThis - nThis2, nLeft, nThis2, aUnder, aother,
                             work, kBlock, jBlock, numberBlocks);
          ClpCholeskyCtriRec(thisStruct, aTri + number_entries(nintri + nbelow), nThis - nThis2, aother, diagonal + nThis2,
                             work + nThis2, nLeft,
                             iBlock - nb, kBlock - nb, numberBlocks - nb);
     }
}
