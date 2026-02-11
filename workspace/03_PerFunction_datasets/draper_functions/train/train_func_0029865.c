ReadPixels(void* pvoid, size_t cbyteAvailable)
{

	if (_rect.Width <= 0)
	{
		_rect.Width = _info.width;
		_rect.Height = _info.height;
	}

	int64_t cbytePlane = (int64_t)(_rect.Width) * _rect.Height * ((_info.bitspersample + 7)/8);

	if (int64_t(cbyteAvailable) < cbytePlane * _info.components)
		throw JlsException(UncompressedBufferTooSmall);

	int scancount = _info.ilv == ILV_NONE ? _info.components : 1;

	BYTE* pbyte = (BYTE*)pvoid;
	for (LONG scan = 0; scan < scancount; ++scan)
	{
		ReadScan(pbyte);
		pbyte += cbytePlane;
	}
}
