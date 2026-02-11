ksigsetmask(int mask)
{
	int		oldmask;

	oldmask = _kio.ki_sigmask;
	mask &= ~SIG_PRIV;
	_kio.ki_sigmask = mask;


	if (_kio.ki_signal) {
		_ksig_follow();
	}

	return(oldmask);
}
