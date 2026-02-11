avrule_node_reset(void *a, void *b __attribute__ ((unused)))
{
	avrule_node_t *an = a;
	if (!a)
		return -1;
	an->used = false;
	return 0;
}
