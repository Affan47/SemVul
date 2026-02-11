OStream(size_t bufferSize, bool extend)
: _buffer(bufferSize, extend)
{
    attachBuffer(&_buffer);
}
