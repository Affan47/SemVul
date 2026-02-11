pointerToMallocMemory(const void * ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	ensureSize(globalAllocCount + 1);
	globalAllocMem[globalAllocCount++] = (GenericPointer)ptr;
}
