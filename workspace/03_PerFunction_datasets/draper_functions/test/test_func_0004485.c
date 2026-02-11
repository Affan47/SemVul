Parse( const char* p, size_t len )
{
	const char* start = p;
    Clear();

    if ( len == 0 || !p || !*p ) {
        SetError( XML_ERROR_EMPTY_DOCUMENT, 0, 0 );
        return _errorID;
    }
    if ( len == (size_t)(-1) ) {
        len = strlen( p );
    }
    _charBuffer = new char[ len+1 ];
    memcpy( _charBuffer, p, len );
    _charBuffer[len] = 0;

    p = XMLUtil::SkipWhiteSpace( p );
    p = XMLUtil::ReadBOM( p, &_writeBOM );
    if ( !p || !*p ) {
        SetError( XML_ERROR_EMPTY_DOCUMENT, 0, 0 );
        return _errorID;
    }

    ptrdiff_t delta = p - start;
    ParseDeep( _charBuffer+delta, 0 );
    if ( Error() ) {


        DeleteChildren();
        _elementPool.Clear();
        _attributePool.Clear();
        _textPool.Clear();
        _commentPool.Clear();
    }
    return _errorID;
}
