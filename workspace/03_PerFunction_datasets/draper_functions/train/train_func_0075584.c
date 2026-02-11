ajSeqBamBgzfSeek(AjPSeqBamBgzf fp, ajlong pos, int where)
{
    int block_offset;
    ajlong block_address;

    if (fp->open_mode != 'r')
    {
	ajErr("file not open for read");
	return -1;
    }

    if (where != SEEK_SET)
    {
	ajErr("unimplemented seek option");
	return -1;
    }

    block_offset = pos & 0xFFFF;
    block_address = (pos >> 16) & 0xFFFFFFFFFFFFLL;

    if (fseek(fp->file, block_address, SEEK_SET) != 0)
    {
	ajErr("seek failed");
	return -1;
    }

    fp->block_length = 0;
    fp->block_address = block_address;
    fp->block_offset = block_offset;

    return 0;
}
