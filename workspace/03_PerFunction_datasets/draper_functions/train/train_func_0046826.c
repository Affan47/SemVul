ffcopy(fitsfile *infptr,
           fitsfile *outfptr,
           int morekeys,
           int *status)


{
    int nspace;

    if (*status > 0)
        return(*status);

    if (infptr == outfptr)
        return(*status = SAME_FILE);

    if (ffcphd(infptr, outfptr, status) )
       return(*status);

    if (morekeys > 0) {
      ffhdef(outfptr, morekeys, status);

    } else {
        if (ffghsp(infptr, NULL, &nspace, status) > 0)
            return(*status);

        if (nspace > 0) {
            ffhdef(outfptr, nspace, status);
            if (nspace >= 35) {


	        ffwend(outfptr, status);
            }
        }
    }

    ffcpdt(infptr, outfptr, status);

    return(*status);
}
