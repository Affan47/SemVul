ReadByte()
{
    if (_cbyteOffset >= _cbyteLength)
	throw JlsException(InvalidCompressedData);

    return _pdata[_cbyteOffset++];
}
