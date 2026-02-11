d_func() const
{
    if (_mobj && _index >= 0 && _index < _mobj->d->properties.size())
        return &(_mobj->d->properties[_index]);
    else
        return 0;
}
