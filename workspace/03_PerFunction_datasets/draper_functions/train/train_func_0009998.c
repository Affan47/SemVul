GetWord (MemGif)
BYTE *MemGif;
{
	register WORD w;
	if (EndianOrder == 1)
	{
		w  = (WORD) (*MemGif++ & 0xFF);
		w |= (WORD) ((*MemGif++ & 0xFF) << 0x08);
	}
	else
	{
		w = (WORD) (*MemGif++ & 0xFF);
		w = ((WORD) (*MemGif++ & 0xFF)) | (w << 0x08);
	}
	return w;
}
