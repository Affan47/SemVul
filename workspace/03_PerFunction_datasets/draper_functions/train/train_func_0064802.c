add_sdsSDG_annotations()
{
    char        labsds[MAXLEN_LAB], labris[MAXLEN_LAB], descsds[MAXLEN_DESC],
                descris[MAXLEN_DESC];
    uint8       pal[768];
    uint16      refnum;
    int32       ret;
    intn        rank;
    int         j;
    int32       dimsizes[2];
    float      *data;
    intn num_errs=0;


    HDstrcpy(labsds, "sdsSDG label #1: sds");
    HDstrcpy(descsds, "sdsSDG Descr #1: 1  2  3  4  5  6  7  8  9 10 11 12 \n");
    HDstrcat(descsds, "             13 14 15 16 17 18 19 20 **END SDS DESCR**\n");
    HDstrcpy(descris, "sdsSDG Descr #2: A B C D E F G H I J K L \n");
    HDstrcat(descris, "                M N O **END IMAGE DESCR **\n");


    data = (float *) HDmalloc(ROWS * COLS * sizeof(float));

    dimsizes[0] = ROWS;
    dimsizes[1] = COLS;

    gen2Dfloat(ROWS, COLS, data);

    ret = DFSDsetdims(2, dimsizes);


    for (j = 0; j < REPS; j++)
      {


          ret = DFSDadddata(DFAN_SDG_FILE, 2, dimsizes, (VOIDP) data);

            {
                refnum = DFSDlastref();
                ret = DFANputlabel(DFAN_SDG_FILE, DFTAG_SDG, refnum, labsds);
                ret = DFANputdesc(DFAN_SDG_FILE, DFTAG_SDG, refnum,
                                  descsds, (int32)HDstrlen(descsds));
            }
      }


    for (j = 0; j < REPS; j++)
      {
          ret = DFSDgetdims(DFAN_SDG_FILE, &rank, dimsizes, 3);
          refnum = DFSDlastref();

          if ((j % 3) != 0)
              num_errs = check_lab_desc(DFAN_SDG_FILE, DFTAG_SDG, refnum, labsds, descsds);
      }

    HDfree((VOIDP) data);
    return 0;
}
