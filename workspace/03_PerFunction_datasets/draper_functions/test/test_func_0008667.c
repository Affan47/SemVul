get(const fn_call& fn) const
{
	ScopedLock lock(*this);
	if (!lock.obtainedLock()) {
		return _underlyingValue;
	}

	if (_getter) return _getter->call(fn);


	return as_value();
}
