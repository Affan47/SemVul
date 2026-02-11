check_if_used(used_gpr_t *gprs, int count, unsigned int gpr)
{
	int i;
	for (i = 0; i < count; i++) {
		if (gprs[i].gpr == gpr)
			return i;
	}
	return -1;
}
