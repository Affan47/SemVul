readChunk(
          AiffChunk      *c,
          FILE           *fp
          )
{
    int             status;
    char            n;

    if ((status = fread(c, sizeof(AiffChunk), 1, fp)))
	if (NAS_LITTLE_ENDIAN)
	    swapl(&c->ckSize, n);

    return status;
}
