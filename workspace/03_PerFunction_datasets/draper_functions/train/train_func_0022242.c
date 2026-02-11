posForward()
{
	if (pos() == lastpos())
		return false;
	++pos();
	return true;
}
