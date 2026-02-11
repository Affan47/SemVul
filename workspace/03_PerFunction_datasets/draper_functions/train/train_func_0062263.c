ClpCholeskyCfactor(ClpCholeskyDenseC * thisStruct, longDouble * a, int n, int numberBlocks,
                   longDouble * diagonal, longDouble * work, int * rowsDropped)
{
     if (n <= BLOCK) {
          ClpCholeskyCfactorLeaf(thisStruct, a, n, diagonal, work, rowsDropped);
     } else {
          int nb = number_blocks((n + 1) >> 1);
          int nThis = number_rows(nb);
          longDouble * aother;
          int nLeft = n - nThis;
          int nintri = (nb * (nb + 1)) >> 1;
          int nbelow = (numberBlocks - nb) * nb;
          ClpCholeskyCfactor(thisStruct, a, nThis, numberBlocks, diagonal, work, rowsDropped);
          ClpCholeskyCtriRec(thisStruct, a, nThis, a + number_entries(nb), diagonal, work, nLeft, nb, 0, numberBlocks);
          aother = a + number_entries(nintri + nbelow);
          ClpCholeskyCrecTri(thisStruct, a + number_entries(nb), nLeft, nThis, nb, 0, aother, diagonal, work, numberBlocks);
          ClpCholeskyCfactor(thisStruct, aother, nLeft,
                             numberBlocks - nb, diagonal + nThis, work + nThis, rowsDropped);
     }
}
