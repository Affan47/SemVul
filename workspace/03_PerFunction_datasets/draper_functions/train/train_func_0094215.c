Strcpy( const char *stg )
{
    size_t len = ::strlen(stg);
    if (len + 1 > _size) {
        if ((_size + _increment) > len)
            _size += _increment;
        else
            _size += len + 1;
    	_buf = (char *)realloc(_buf, _size);
        if (!_buf) {
            ::printf("%s: ERROR: Memory allocation FAILED!\n", mod_name);
            exit(1);
        }
    }
    ::strcpy(_buf,stg);
    _strlen = ::strlen(_buf);
    return _buf;
}
