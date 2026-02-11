tr_byxxx_init(tr_byxxx_p _bxp, int _nr)
{
	if(!_bxp)
		return -1;
	_bxp->nr = _nr;
	if (_bxp->flags & PKG_ALLOC)
		_bxp->xxx = (int*)pkg_malloc(_nr*sizeof(int));
	else
		_bxp->xxx = (int*)shm_malloc(_nr*sizeof(int));
	if(!_bxp->xxx)
		return -1;
	if (_bxp->flags & PKG_ALLOC)
		_bxp->req = (int*)pkg_malloc(_nr*sizeof(int));
	else
		_bxp->req = (int*)shm_malloc(_nr*sizeof(int));
	if(!_bxp->req)
	{
		if (_bxp->flags & PKG_ALLOC)
			pkg_free(_bxp->xxx);
		else
			shm_free(_bxp->xxx);
		return -1;
	}

	memset(_bxp->xxx, 0, _nr*sizeof(int));
	memset(_bxp->req, 0, _nr*sizeof(int));

	return 0;
}
