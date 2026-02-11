readDOUBLEZimage(FILE *fp,int nx, int ny, int nz, endianness e)
{
    double *retbuf;
    int  ns;
    long imlength, nbread;

    imlength = nx*ny*nz;

    retbuf = (double *)malloc(nx*ny*nz * sizeof(double));

    if (retbuf == 0) {
	errprintf("readDOUBLEZimage: not enough memory to load file\n");
	return 0;
    }

    nbread = fread(retbuf, sizeof(double), imlength, fp);
    if (nbread != imlength) {
	errprintf("readDOUBLEZimage: incomplete image\n");

	memset(retbuf+nbread, 0, (imlength-nbread)*sizeof(double));
    }

    ns = 2;
    if (((e != ENDIAN_UNKNOWN) && (e != checkendian()))
        || ((e == ENDIAN_UNKNOWN) && ((ns = needswapdouble(retbuf, imlength)) == 1))) {
	dbgprintf("Image buffer will be swapped\n");
	swapdoublebuf(retbuf, imlength);
    } else if (ns == -1) {


        errprintf("readDoubleZImage: cannot make sense of image\n because of invalid double precision values present\n");
	free(retbuf);
	retbuf = 0;
    } else {
	dbgprintf("Image buffer will not be swapped\n");
    }

    return retbuf;
}
