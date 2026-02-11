__env_get_chunk(infop, nextp, sizep)
	REGINFO *infop;
	void **nextp;
	uintmax_t *sizep;
{
	REGION_MEM *mem;

	if (infop->mem == NULL)
		return (NULL);
	if (*nextp == NULL)
		*nextp = infop->mem;
	mem = *(REGION_MEM **)nextp;
	*nextp = mem->next;

	*sizep = __env_elem_size(infop->env, mem);
	*sizep -= sizeof(*mem);

	return ((void *)(mem + 1));
}
