memGetc(memBuf_t *mp)
{
	return memEof(mp) ? EOF : (int)(*(unsigned char *)(mp->readptr++));
}
