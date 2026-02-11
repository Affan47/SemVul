get_integer(IndexBuffer *buf) {
    unsigned char i;
    int r;
    int negative=0;

    i=get_byte(buf);
    if (i==NEGATIVE_NUMBER_TAG) {
	negative=1;
	i=get_byte(buf);
    }
    if (i==END_OF_POSTINGS_TAG) {

	return INT_MAX;
    }
    else if (i<127) r=i;
    else if ((i&(128+64))==128) {

	r=((i&63)<<8)|get_byte(buf);
    }
    else if ((i&(128+64+32))==128+64) {

	r=(i&31)<<16|(get_byte(buf)<<8);
	r=r|get_byte(buf);
    }
    else if ((i&(128+64+32+16))==128+64+32) {

	r=(i&15)<<24|(get_byte(buf)<<16);
	r|=get_byte(buf)<<8;
	r=r|get_byte(buf);
    } else if(i==0xf0) {

	r=get_byte(buf)<<24;
	r|=get_byte(buf)<<16;
	r|=get_byte(buf)<<8;
	r|=get_byte(buf);
    } else {
	assert(0 && "Corrupted index file");
	abort();
    }
    return (negative)?-r:r;
}
