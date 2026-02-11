b64_encode(const string &src, string &dst)
{
	unsigned int bits = 0;
	int char_count = 0, i = 0;

	dst = "";
	string::size_type len = src.size();
	while (len--) {
		unsigned int c = (unsigned char)src[i++];
		bits += c;
		char_count++;
		if (char_count == 3) {
			dst += b64[bits >> 18];
			dst += b64[(bits >> 12) & 0x3f];
			dst += b64[(bits >> 6) & 0x3f];
	    		dst += b64[bits & 0x3f];
		    	bits = 0;
		    	char_count = 0;
		} else	{
	    		bits <<= 8;
		}
    	}
	if (char_count != 0) {
		bits <<= 16 - (8 * char_count);
		dst += b64[bits >> 18];
		dst += b64[(bits >> 12) & 0x3f];
		if (char_count == 1) {
			dst += '-';
			dst += '-';
		} else {
			dst += b64[(bits >> 6) & 0x3f];
			dst += '-';
		}
	}
	return dst;
}
