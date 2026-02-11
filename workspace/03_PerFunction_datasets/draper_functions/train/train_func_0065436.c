__ExDictionaryCreate (int size, int local,
						int locking, int sorted)
{
    int			n;
    EXDictionary	d;
    Error		l;

#ifdef DICT_TIMING
DXMarkTimeLocal("D create");
#endif


    size    = (size <= 0) ? 1 : _dxf_ExNextPowerOf2 (size);
    locking = local ? FALSE : locking;


    n  = sizeof (_EXDictionary);
    n += sizeof (_EXDictHead) * size;

    d = (EXDictionary) (local ? DXAllocateLocal (n) : DXAllocate (n));
    if (! d)
	_dxf_ExDie ("_dxf_ExDictionaryCreate:  DXAllocate failed");

    ExZero (d, n);

    d->mask	= size - 1;
    d->locking	= locking;
    d->size	= size;
    d->local	= local;

    d->sorted   = sorted;
    d->newest   = NULL;
    d->oldest   = NULL;

    if (locking)
    {
	l = DXcreate_lock (&d->lock, "Dictionary");
	if (l != OK)
	    _dxf_ExDie ("_dxf_ExDictionaryCreate:  DXcreate_lock failed");
    }

#ifdef DICT_TIMING
DXMarkTimeLocal("-D create");
#endif
    return (d);
}
