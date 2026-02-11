handle_control_8(unsigned char *src,  int slen,
			    unsigned char *dest, int dlen)
{
    int s,d;

    for (s = 0, d = 0; s < slen && d < dlen;) {
	if (src[s] >= 0x80  &&  src[s] <= 0x9f) {
	    switch (src[s]) {
	    case 0x86:
	    case 0x87:
		s++;
		break;
	    case 0x1a:
		dest[d++] = ' ';
		s++;
		break;
	    case 0x8a:
		dest[d++] = '\n';
		s++;
		break;
	    default:
		s++;
	    }
	} else {
	    dest[d++] = src[s++];
	}
    }
    return d;
}
