do_bset(int cap_ordinal)
{
	int ret;

	ret = prctl(PR_CAPBSET_READ, cap_ordinal);
	if (ret == 1) {
		ret = prctl(PR_CAPBSET_DROP, cap_ordinal);
		if (ret != 0)
			fail("Error dropping capability %s from bset\n",
			     capabilities[cap_ordinal].cap_name);
	} else if (ret < 0)
		fail("Kernel doesn't recognize capability %d\n", cap_ordinal);
}
