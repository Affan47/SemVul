zoomouth(uchar *outbuf,
		     const uchar *inbuf,
		     int oh,
		     int d,
		     int iw,
		     int x,
		     int y,
		     int w,
		     int h)
{
    int                     i, j, k;
    long                    ey, inc1y, inc2y;
    uchar                   *op;
    const uchar             *ip;


    for (j = 0 ; j < w ; j++) {

	ey = 2*oh -h;
	inc1y = 2 * (oh - h);
	inc2y = 2 * oh;

	op = outbuf + j * d;

	ip = inbuf + d * ((x+j) + y*(long)iw);


	for (i = 0 ; i < h ; i++) {
	    if (ey > 0) {

		for (k = 0 ; k < d ; k++) {
		    *(op+k) = *(ip+k);
		}
		op += w * d;
		ey += inc1y;
	    } else {
		ey += inc2y;
	    }
	    ip +=  iw * d;
	}
    }
}
