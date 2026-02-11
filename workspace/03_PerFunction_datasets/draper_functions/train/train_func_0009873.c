prepareRequest(const String& name, IDecomposer** argv, unsigned argc)
{
    if (_domain.empty())
        _stream << '\xc0' << name << '\0';
    else
        _stream << '\xc3' << _domain << '\0' << name << '\0';

    for(unsigned n = 0; n < argc; ++n)
    {
        argv[n]->format(_formatter);
    }

    _stream << '\xff';
}
