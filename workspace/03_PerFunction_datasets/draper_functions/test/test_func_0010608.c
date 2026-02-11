ois_convert_to_ia5(char *str, const char *raw, int len)
{
    int j;
    int i;
    int ch;

    SAY2(3, "ois_convert_to_ia5 len=%d", len);

    for (j = i = 0; i < len; ++i) {
	ch = raw[i] & 0xff;
	if (ch == 0x5c || ch == 0x5e || ch == 0x60 || ch == 0x7e) {
  	    str[j++] = (char) 0x5c;
  	    str[j++] = (char) ch;
	} else if (0x20 <= ch && ch < 0x7f) {
	    str[j++] = (char) ch;
	} else if (0x00 <= ch && ch < 0x20) {
	    str[j++] = (char) 0x5e;
	    str[j++] = (char) ch + 0x40;
	} else if (0xa0 <= ch && ch < 0xff) {
	    str[j++] = (char) 0x60;
	    str[j++] = (char) ch - 0x80;
	} else if (0x80 <= ch && ch < 0xa0) {
	    str[j++] = (char) 0x7e;
	    str[j++] = (char) ch - 0x40;
	} else if (ch == 0x7f) {
	    str[j++] = (char) 0x5e;
	    str[j++] = (char) 0x7e;
	} else {
	    str[j++] = (char) 0x7e;
	    str[j++] = (char) 0x7e;
	}
    }

    str[j] = '\0';
    SAY2(5, "ois_convert_to_ia5 gave [%s]", ois_debug_str(str, j));
    return j;
}
