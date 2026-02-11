input_addr_to_csrow(struct mem_ctl_info *mci, u64 input_addr)
{
	struct amd64_pvt *pvt;
	int csrow;
	u64 base, mask;

	pvt = mci->pvt_info;

	for_each_chip_select(csrow, 0, pvt) {
		if (!csrow_enabled(csrow, 0, pvt))
			continue;

		get_cs_base_and_mask(pvt, csrow, 0, &base, &mask);

		mask = ~mask;

		if ((input_addr & mask) == (base & mask)) {
			edac_dbg(2, "InputAddr 0x%lx matches csrow %d (node %d)\n",
				 (unsigned long)input_addr, csrow,
				 pvt->mc_node_id);

			return csrow;
		}
	}
	edac_dbg(2, "no matching csrow for InputAddr 0x%lx (MC node %d)\n",
		 (unsigned long)input_addr, pvt->mc_node_id);

	return -1;
}
