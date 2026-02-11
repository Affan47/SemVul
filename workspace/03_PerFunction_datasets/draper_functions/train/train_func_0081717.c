operator=(const pty &rhs)
{
	if (this == &rhs)
		return *this;
	_slave = dup(rhs._slave); _master = dup(rhs._master);
	m = rhs.m; s = rhs.s;
	return *this;
}
