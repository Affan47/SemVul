f12h_mc0_mce(u16 ec, u8 xec)
{
	bool ret = false;

	if (MEM_ERROR(ec)) {
		u8 ll = LL(ec);
		ret = true;

		if (ll == LL_L2)
			pr_cont("during L1 linefill from L2.\n");
		else if (ll == LL_L1)
			pr_cont("Data/Tag %s error.\n", R4_MSG(ec));
		else
			ret = false;
	}
	return ret;
}
