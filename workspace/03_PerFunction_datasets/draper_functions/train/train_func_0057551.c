CopyBytes(unsigned short int aus[64],
          const unsigned char ac[128],
          const unsigned int nz, const unsigned int ioff, const unsigned int nzg, const unsigned int ioffg)
{

    unsigned int i, j;

    i = 0;
    memset(aus, 0, 64 * sizeof(unsigned short int));
    for (j = 0; j < nz; ++j, i += 2)
        aus[ioff + j] = ac[i] | ac[i + 1] << 8;

    for (j = 0; j < nzg; ++j, i += 2)
        aus[32 + ioffg + j] = ac[i] | ac[i + 1] << 8;
}
