del_assertion(void *va)
{
	struct assert *a = va;
	size_t i;

	for (i = 0; i < a->nbval; i ++) del_token_fifo(a->val + i);
	if (a->nbval) freemem(a->val);
	freemem(a);
}
