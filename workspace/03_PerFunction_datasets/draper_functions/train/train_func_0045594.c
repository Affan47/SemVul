ReadSGIImage(const SoInput& in, int &w, int &h, int &nc,
						unsigned char *&bytes) {

    i_seterror(errfunc);

    IMAGE *image_in;
    int i, j, row;

    if ( (image_in = fiopen(fileno(in.getCurFile()), "r")) == NULL)
	return FALSE;

    w = image_in->xsize;
    h = image_in->ysize;
    nc = image_in->zsize;

    bytes = new unsigned char[w*h*nc];

    short *rbuf = new short[w];

    int readOK = TRUE;

    for (row = 0; row < h; row++) {
	for (i = 0; i < nc; i++) {
	    if (getrow(image_in, rbuf, row, i) < 0) {
		row = h;
		readOK = FALSE;
		break;
	    }
	    for (j = 0; j < w; j++) {
		bytes[row*w*nc + j*nc + i] =
		    (unsigned char) rbuf[j];
	    }
	}
    }
    delete [] rbuf;

    iclose(image_in);

    return TRUE;
}
