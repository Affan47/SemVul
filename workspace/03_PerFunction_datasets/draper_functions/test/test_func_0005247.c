wait_key_set(poll_table *wait, unsigned long in,
				unsigned long out, unsigned long bit,
				unsigned int ll_flag)
{
	wait->_key = POLLEX_SET | ll_flag;
	if (in & bit)
		wait->_key |= POLLIN_SET;
	if (out & bit)
		wait->_key |= POLLOUT_SET;
}
