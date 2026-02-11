GetDistCompressed(unsigned short int aus[64], const bearoffcontext * pbc, const unsigned int nPosID)
{
    unsigned char *puch;
    unsigned char ac[128];
    unsigned int iOffset;
    unsigned int nBytes;
    unsigned int ioff, nz, ioffg = 0, nzg = 0;
    unsigned int nPos = Combination(pbc->nPoints + pbc->nChequers, pbc->nPoints);
    unsigned int index_entry_size = pbc->fGammon ? 8 : 6;


    if (pbc->p)

        puch = pbc->p + 40 + nPosID * index_entry_size;
    else {
        ReadBearoffFile(pbc, 40 + nPosID * index_entry_size, ac, index_entry_size);
        puch = ac;
    }


    iOffset = MakeInt(puch[0], puch[1], puch[2], puch[3]);

    nz = puch[4];
    ioff = puch[5];
    if (pbc->fGammon) {
        nzg = puch[6];
        ioffg = puch[7];
    }


    if ((iOffset > 64 * nPos && 64 * nPos > 0) || nz > 32 || ioff > 32 || nzg > 32 || ioffg > 32) {
        fprintf(stderr,
                "The bearoff file '%s' is likely to be corrupted.\n"
                "Please check that the MD5 sum is the same as documented "
                "in the GNU Backgammon manual.\n"
                "Offset %lu, dist size %u (offset %u), "
                "gammon dist size %u (offset %u)\n", pbc->szFilename, (unsigned long) iOffset, nz, ioff, nzg, ioffg);
        g_assert_not_reached();
    }


    iOffset = 40
        + nPos * index_entry_size
        + 2 * iOffset;


    nBytes = 2 * (nz + nzg);


    if (pbc->p)

        puch = pbc->p + iOffset;
    else {

        ReadBearoffFile(pbc, iOffset, ac, nBytes);
        puch = ac;

    }

    CopyBytes(aus, puch, nz, ioff, nzg, ioffg);

    return aus;
}
