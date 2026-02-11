Write(BYTE* pdata, size_t cbyteLength)
{
	_pdata = pdata;
	_cbyteLength = cbyteLength;

	WriteByte(0xFF);
	WriteByte(JPEG_SOI);

	for (size_t i = 0; i < _segments.size(); ++i)
	{
		_segments[i]->Write(this);
	}


	WriteByte(0xFF);
	WriteByte(JPEG_EOI);

	return _cbyteOffset;
}
