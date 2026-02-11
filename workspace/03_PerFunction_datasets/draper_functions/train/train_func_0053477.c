truncatePrefixFromConfig( char * src,  char * dst, char length){

	int i=0;
	dst[0]=0;

	for(i=0;i<length/8;i++) {
	    sprintf(dst + strlen(dst), "%02x", src[i]);
	    if (i && (i%2))
		sprintf(dst+strlen(dst), ":");
	}
	if (i%2)
	    sprintf(dst+strlen(dst), "::");
	else
	    sprintf(dst+strlen(dst), ":");
}
