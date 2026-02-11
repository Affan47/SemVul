__bm_unmap(unsigned long *p_addr)
{
	kunmap_atomic(p_addr);
}
