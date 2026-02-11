basic_stringstream(ios_base::openmode mode)
: basic_iostream<cxxtools::Char>(0)
, _buffer(mode)
{
    init(&_buffer);
}
