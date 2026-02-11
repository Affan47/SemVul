base_limit_match(struct amd64_pvt *pvt, u64 sys_addr, u8 nid)
{
	u64 addr;


	addr = sys_addr & 0x000000ffffffffffull;

	return ((addr >= get_dram_base(pvt, nid)) &&
		(addr <= get_dram_limit(pvt, nid)));
}
