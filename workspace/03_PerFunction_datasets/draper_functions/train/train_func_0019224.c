read(void *aBuf, uint size)
{
	FileOfs mofs;
	FileOfs msize;
	int c = 0;
	byte *buf = (byte *)aBuf;
	while (size) {
		uint s = size;
		if (!map_ofs(ofs, &mofs, &msize)) break;
		if (s > msize) s = msize;
		mFile->seek(mofs);
		s = mFile->read(buf, s);
		if (!s) break;
		buf += s;
		size -= s;
		c += s;
		ofs += s;
	}
	return c;
}
