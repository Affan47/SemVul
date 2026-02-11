allocate(unsigned int size)
{
    if (!ensureSpace(size)) return 0;

    _reservation = 0;
    void* result = _last->space + _last->used;
    _last->used += size;

    _count++;
    _size += size;

    return result;
}
