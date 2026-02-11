lock_recursive (void)
{
	int old_count;
	do {
	retry:
		old_count = binary_protocol_use_count;
		if (old_count < 0) {


			goto retry;
		}
	} while (InterlockedCompareExchange (&binary_protocol_use_count, old_count + 1, old_count) != old_count);
	mono_memory_barrier ();
}
