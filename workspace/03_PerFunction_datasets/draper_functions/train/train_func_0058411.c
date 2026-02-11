cacheReadOneBlock( const IORequest &req ) const
{


    if((req.offset == _cache.offset) && (_cache.dataLen != 0))
    {

	int len = req.dataLen;
	if(_cache.dataLen < len)
	    len = _cache.dataLen;
	memcpy( req.data, _cache.data, len );
	return len;
    } else
    {
	if(_cache.dataLen > 0)
	    clearCache( _cache, _blockSize );


	IORequest tmp;
	tmp.offset = req.offset;
	tmp.data = _cache.data;
	tmp.dataLen = _blockSize;
	ssize_t result = readOneBlock( tmp );
	if(result > 0)
	{
	    _cache.offset = req.offset;
	    _cache.dataLen = result;
	    if(result > req.dataLen)
		result = req.dataLen;
	    memcpy( req.data, _cache.data, result );
	}
	return result;
    }
}
