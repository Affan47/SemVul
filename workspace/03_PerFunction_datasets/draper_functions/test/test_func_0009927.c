ReadMP3ID3v1Tag(FILE *fi, unsigned char **tagbuff, long *tag_offset) {
    char tmp[128];

	if ( *tag_offset < 128 ) return 0;
	if ( fseek(fi, *tag_offset - 128,SEEK_SET) ) return 0;
	if ( fread(tmp, 1, 128, fi) != 128 ) return 0;
    if ( memcmp (tmp, "TAG", 3) ) return 0;


	if (*tagbuff)
		free(*tagbuff);
	*tagbuff = (unsigned char *)malloc(128);
    memcpy(*tagbuff,tmp,128);
    *tag_offset -= 128;

    return 1;
}
