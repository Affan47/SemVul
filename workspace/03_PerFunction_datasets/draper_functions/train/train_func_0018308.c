sdata() {
    int x;
    if (cx || cz) {
	if (debug)
	  fprintf(db,"sdata interrupted cx = %d cz = %d\n",cx,cz);
	failure = 1;
	return(0);
    }
    x = getpkt(maxsiz);
    if (x < 1) {
	if (debug)
	  fprintf(db,"sdata getpkt = %d\n",x);
	return(0);
    }
    nxtpkt();
    return(spacket('D',seq,x,xdata));
}
