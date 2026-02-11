_setFloat(long double value)
{
    if (_t != t_float)
    {
        _releaseValue();
        _t = t_float;
    }

    _u._f = value;

    _category = Value;
}
