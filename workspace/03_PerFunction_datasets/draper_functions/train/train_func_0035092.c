copy_string(char *dst, const char *src, int maxlen)
{
    int i;

    for (i = 0; i < maxlen; i++) {
	if (src[i] == ' ' || i == maxlen - 1) {
	    dst[i] = 0;
	    break;
	}
	else {
	    dst[i] = src[i];
	}
    }
    return i;
}
