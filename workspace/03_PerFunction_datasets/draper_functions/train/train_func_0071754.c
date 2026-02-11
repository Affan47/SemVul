DXPrintMemoryInfo()
{
    uint i;
    ulong total;

    switch (m) {
      case MEM_NOTINIT:
	DXMessage("memory not initialized yet");
	return;

      case MEM_DATASEG:
	DXMessage("using data segment for arenas; sbrk called %d times",
		  num_sbrk_calls);
	if (num_failed_calls > 0) {
	    DXMessage("sbrk failed %d times", num_failed_calls);
	    num_sbrk_calls -= num_failed_calls;
	}
	for (i=0; i<min(num_sbrk_calls, MAX_CHUNKS); i++)
	    DXMessage("sbrk %d returned 0x%08x, %lu bytes allocated",
		      i+1, alloc_addr_start[i],
		      (ulong)SUB_PTR(alloc_addr_end[i], alloc_addr_start[i]));

#if !defined(cygwin) && !defined(macos)
	DXMessage("end address = 0x%08x, data segment extended by %lu bytes",
		  alloc_addr_end[i-1],
		  (ulong)SUB_PTR(alloc_addr_end[i-1], &end));
#endif
	return;

      case MEM_SHARED:
	DXMessage("using %d shared memory chunks(s) for arenas", alloc_chunks);
	total = 0;
	for (i=0; i<min(alloc_chunks, MAX_CHUNKS); i++) {
	    DXMessage("chunk %d starts at 0x%08x, %lu bytes long (%d segments)",
		      i+1, alloc_addr_start[i],
		      (ulong)SUB_PTR(alloc_addr_end[i], alloc_addr_start[i]),
		      alloc_segments[i]);
	    total += (ulong)SUB_PTR(alloc_addr_end[i], alloc_addr_start[i]);
	}
	if (i > 1)
	    DXMessage("end address = 0x%08x, total shared memory = %lu bytes",
		      alloc_addr_end[i-1], total);
	else
	    DXMessage("end address = 0x%08x", alloc_addr_end[0]);
	return;
    }
    return;
}
