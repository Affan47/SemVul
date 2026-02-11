egg_test_wait_until (int timeout)
{
	g_assert (wait_until_impl != NULL);
	return (wait_until_impl) (timeout);
}
