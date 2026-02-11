read(void* buffer, u32 sizeToRead)
{
#if 1
	if (0 == File)
		return 0;

	s32 r = AreaStart + Pos;
	s32 toRead = core::s32_min(AreaEnd, r + sizeToRead) - core::s32_max(AreaStart, r);
	if (toRead < 0)
		return 0;
	File->seek(r);
	r = File->read(buffer, toRead);
	Pos += r;
	return r;
#else
	const long pos = File->getPos();

	if (pos >= AreaEnd)
		return 0;

	if (pos + (long)sizeToRead >= AreaEnd)
		sizeToRead = AreaEnd - pos;

	return File->read(buffer, sizeToRead);
#endif
}
