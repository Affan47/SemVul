_fin_external_locking(void)
{
	if (_end_fn)
		_end_fn();

	dlclose(_locking_lib);

	_locking_lib = NULL;
	_init_fn = NULL;
	_end_fn = NULL;
	_lock_fn = NULL;
	_reset_fn = NULL;
}
