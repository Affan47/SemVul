kstrdup_const(const char *s, gfp_t gfp)
{
	if (is_kernel_rodata((unsigned long)s))
		return s;

	return kstrdup(s, gfp);
}
