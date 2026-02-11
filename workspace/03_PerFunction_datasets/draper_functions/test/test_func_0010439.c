quantize(size_t size) {
	int remainder;


	remainder = size % P_SIZE;
	if (remainder != 0)
		size += P_SIZE - remainder;
#if defined(DEBUGGING_MEMCLUSTER)
	return (size + SMALL_SIZE_LIMIT + sizeof (int));
#else
	return (size);
#endif
}
