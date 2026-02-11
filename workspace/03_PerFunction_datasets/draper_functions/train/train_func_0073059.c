memUngetc(memBuf_t *mp)
{
	if (mp->readptr > mp->memory)
		mp->readptr--;
}
