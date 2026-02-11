memsize_801(void)
{
	ulong mem_size;


	if (alt_mem_k < ext_mem_k) {
		mem_size = ext_mem_k;
	} else {
		mem_size = alt_mem_k;
	}

	v->pmap[0].start = 0;
	v->pmap[0].end = RES_START >> 12;
	v->test_pages = RES_START >> 12;


	v->pmap[1].start = (RES_END + 4095) >> 12;
	v->pmap[1].end = (mem_size + 1024) >> 2;
	v->test_pages += mem_size >> 2;
	v->msegs = 2;
}
