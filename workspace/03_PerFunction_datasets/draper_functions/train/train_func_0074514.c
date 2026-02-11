alloc ()
{
	void* ptr;

	DEBUG_TRACE (DEBUG::Pool, string_compose ("%1 %2 has %3 pending free entries waiting\n", pthread_self(), name(), pending.read_space()));
	while (pending.read (&ptr, 1) == 1) {
		DEBUG_TRACE (DEBUG::Pool, string_compose ("%1 %2 pushes back a pending free list entry before allocating\n", pthread_self(), name()));
		free_list.write (&ptr, 1);
	}
	return Pool::alloc ();
}
