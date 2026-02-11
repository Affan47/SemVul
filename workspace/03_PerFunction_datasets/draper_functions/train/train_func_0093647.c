load_pgm_raw(FILE *fp,
			int   start[3],
			int   end[3],
			pixtype *pixtype,
			imgtype *imgtype,
			void **inbuffp)
{
    int            retval = 0;
    void         **buffp;
    int            ncol, nrow, nslice, maxgrey, k, j, i;
    unsigned char *cp;
    unsigned short *sp;

    garbage = false;
    numgot = 0;

    ncol = getint(fp);
    nrow = getint(fp);
    nslice = getint(fp, IV_OPTIONAL);
    nslice = (nslice == 0) ? 1:nslice;

    maxgrey = getint(fp, IV_FINAL);

    dbgprintf("load_pgm_raw: (%dx%dx%d), %d grey-levels\n", ncol,nrow,nslice,maxgrey);

    if (maxgrey <= 1)
	*pixtype = IM_BINARY;
    else if (maxgrey <= 255)
	*pixtype = IM_UINT1;
    else *pixtype = IM_UINT2;

    *imgtype = IM_SPECTRUM;

    start[0] = 0;
    start[1] = 0;
    start[2] = 0;
    end[0] = ncol-1;
    end[1] = nrow-1;
    end[2] = nslice-1;

    buffp = (void **)malloc(sizeof(void *));

    if ((*pixtype == IM_BINARY) || (*pixtype == IM_UINT1)) {

	buffp[0] = malloc((long)ncol*(long)nrow*(long)nslice*sizeof(unsigned char));
	cp = (unsigned char *)(buffp[0]);
	numgot = fread(cp, (size_t) 1, (size_t) ((long)nrow*(long)ncol*(long)nslice), fp);
    } else {
	buffp[0] = malloc((long)ncol*(long)nrow*(long)nslice*sizeof(unsigned short));
	sp = (unsigned short *)(buffp[0]);
        for (k = 0 ; k < nslice ; ++k) {
            for (j = 0 ; j < nrow ; j++) {
                for (i = 0 ; i < ncol ; i++) {
                    *sp++ = getshort(fp);
                }
            }
        }
    }

    *inbuffp = buffp;

    return retval;
}
