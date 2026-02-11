VocOpenFileForWriting(
                      const char *name,
                      VocInfo        *vi
                      )
{
    int             n;

    vi->writing = vi->dataSize = 0;

    if (!(vi->fp = fopen(name, AU_WRITE_BINARY)) ||
	!fwrite(VOC_ID, VOC_ID_SIZE, 1, vi->fp) ||
	!FileWriteS(VOC_DATA_OFFSET, vi->fp, NAS_BIG_ENDIAN) ||
	!FileWriteS(VOC_VERSION, vi->fp, NAS_BIG_ENDIAN) ||
	!FileWriteS(VOC_VERSION_CHK, vi->fp, NAS_BIG_ENDIAN))
	Err();

    if ((n = strlen(vi->comment)))
    {
	fputc(VOC_TEXT, vi->fp);
	n++;
	WriteSize(n);

	if (!fwrite(vi->comment, n, 1, vi->fp))
	    Err();
    }

    if (vi->tracks == 2)
    {
	fputc(VOC_EXTENDED, vi->fp);
	WriteSize(4);
	n = 65536 - (256000000 / (vi->sampleRate * 2));
	fputc(n, vi->fp);
	fputc(n >> 8, vi->fp);
	fputc(0, vi->fp);
	fputc(1, vi->fp);
    }

    fputc(VOC_DATA, vi->fp);
    vi->dataOffset = ftell(vi->fp);
    WriteSize(0);
    fputc(256 - (1000000 / vi->sampleRate), vi->fp);
    fputc(0, vi->fp);

    vi->writing = 1;
    return vi;
}
