htable_new(size_t size, const Comparable_vtable *key_method){
	size = next_prime(max(size, 1U));
	return memcpy(LINKED_MALLOC(sizeof(htable)), &(htable){
		.m_max_size = size,
		.data_method = key_method,
		.size = 0,
		.m_collision = 0,
		.m_array = (__typeof__(((htable*)NULL)->m_array))allocate_set(sizeof(((htable*)NULL)->m_array[0])*size, 0)
	}, sizeof(htable));
}
