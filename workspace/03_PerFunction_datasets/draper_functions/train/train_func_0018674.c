valid_pos(loff_t pos, size_t count)
{
	if (pos < 0 || (long) pos != pos || (ssize_t) count < 0)
		return false;
	if ((unsigned long) pos + (unsigned long) count < (unsigned long) pos)
		return false;
	return true;
}
