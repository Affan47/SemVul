dummy_free(void *mem_)
{
	char *mem = mem_;
	tt_want(check_dummy_mem_ok(mem_));
	mem -= 16;
	free(mem);
}
