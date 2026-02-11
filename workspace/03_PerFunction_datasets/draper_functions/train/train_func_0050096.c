hexbuf(char *dst,int dst_len,const unsigned char *bin,int bytes,int flag)
{
    int charcount = 0;
    const char *start = dst;
    const char *fmt = (flag & HEXBUF_UPPERCASE) ? "%02X" : "%02x";

    *dst = 0;
    while(bytes>0 && dst_len > 3){
	sprintf(dst,fmt,*bin);
	dst += 2;
	bin += 1;
	dst_len -= 2;
	bytes--;
	charcount++;

	bool add_spaces = false;
	if(flag & HEXBUF_SPACE2) add_spaces = true;
	if((flag & HEXBUF_SPACE4) && charcount%2==0){
	    *dst++ = ' ';
	    *dst   = '\000';
	    dst_len -= 1;
	}
    }
    return start;
}
