TSLookup(const int nUs, const int nThem,
         const int UNUSED(nTSP), const int UNUSED(nTSC),
         short int arEquity[4], const int n, const int fCubeful, FILE * pfTmp)
{

    int iPos = CalcPosition(nUs, nThem, n);
    unsigned char ac[8];
    int i;
    unsigned short int us;


    if (fseek(pfTmp, iPos * (fCubeful ? 8 : 2), SEEK_SET) < 0) {
        perror("temp file");
        exit(-1);
    }

    if (fread(ac, 1, 8, pfTmp) < 8) {
        if (errno)
            perror("temp file");
        else
            fprintf(stderr, "error reading temp file\n");
        exit(-1);
    }


    if (fseek(pfTmp, 0L, SEEK_END) < 0) {
        perror("temp file");
        exit(-1);
    }

    for (i = 0; i < (fCubeful ? 4 : 1); ++i) {
        us = ac[2 * i] | ac[2 * i + 1] << 8;
        arEquity[i] = us - 0x8000;
    }

    ++cLookup;

}
