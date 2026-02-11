release_pipelock_teardown (int *lock)
{
	while (1) {
		int lockvalue = mph_int_get (lock);
		int lockvalue_new = lockvalue & ~PIPELOCK_TEARDOWN_BIT;

		if (mph_int_test_and_set (lock, lockvalue, lockvalue_new))
			return;
	}
}
