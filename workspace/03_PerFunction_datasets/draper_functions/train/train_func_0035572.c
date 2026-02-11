operator=(const DirectoryIterator& it)
{
    if (_impl == it._impl)
        return *this;

    if (_impl && 0 == _impl->deref())
    {
        delete _impl;
    }

    _impl = it._impl;

    if (_impl)
        _impl->ref();

    return *this;
}
