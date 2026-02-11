canwlock(RWLock *l)
{
	if(_wlock)
		return (*_wlock)(l, 0, getcallerpc(&l));
	else{
		if(l->writer || l->readers)
			return 0;
		l->writer = (void*)1;
		return 1;
	}
}
