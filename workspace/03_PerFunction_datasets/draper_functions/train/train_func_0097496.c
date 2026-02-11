decl_count(void* buffer)
{

	if(_msgpack_sync_decr_and_fetch((volatile _msgpack_atomic_counter_t*)buffer) == 0) {
		free(buffer);
	}
}
