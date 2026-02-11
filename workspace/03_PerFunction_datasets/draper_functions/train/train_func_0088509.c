ReadMP3Lyrics3v2Tag ( FILE *fp, unsigned char **tagbuff, unsigned long *tagSize, unsigned char **id3tagbuff, long *tag_offset )
{
	int                                 len;
	struct Lyrics3TagFooterStruct       T;
    char                                tmpid3[128];
    char                                tmp[11];
    long                                taglen;

	if ( *tag_offset < 128 ) return 0;
    if ( fseek (fp, *tag_offset - 128, SEEK_SET) ) return 0;
    if ( fread (tmpid3, 1, 128, fp) != 128 ) return 0;

    if ( memcmp (tmpid3, "TAG", 3) ) return 0;

	if (*id3tagbuff)
		free(*id3tagbuff);
	*id3tagbuff = (unsigned char *)malloc(128);
    memcpy(*id3tagbuff,tmpid3,128);
    if ( fseek (fp, *tag_offset - 128 - sizeof (T), SEEK_SET) ) return 0;
    if ( fread (&T, 1, sizeof (T), fp) != sizeof (T) ) return 0;

    if ( memcmp (T.ID, "LYRICS200", sizeof (T.ID)) ) return 0;
	len = Lyrics3GetNumber6 (T.Length);
	if ( fseek (fp, *tag_offset - 128 - (int)sizeof (T) - len, SEEK_SET) ) return 0;
    if ( fread  (tmp, 1, 11, fp) != 11 ) return 0;
    if ( memcmp (tmp, "LYRICSBEGIN", 11) ) return 0;

    taglen = 128 + Lyrics3GetNumber6(T.Length) + sizeof(T);

    *tag_offset -= taglen;
    if (*tagbuff != NULL) {
        free(*tagbuff);
    }
    *tagbuff = (unsigned char *)malloc(taglen);
    fseek(fp,*tag_offset,SEEK_SET);
    fread(*tagbuff,1,taglen,fp);
	*tagSize = taglen;
    return 1;
}
