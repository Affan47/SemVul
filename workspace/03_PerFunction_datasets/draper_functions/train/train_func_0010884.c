rrpc_l2p_update(u64 slba, u32 nlb, __le64 *entries, void *private)
{
	struct rrpc *rrpc = (struct rrpc *)private;
	struct nvm_dev *dev = rrpc->dev;
	struct rrpc_addr *addr = rrpc->trans_map + slba;
	struct rrpc_rev_addr *raddr = rrpc->rev_trans_map;
	sector_t max_pages = dev->total_pages * (dev->sec_size >> 9);
	u64 elba = slba + nlb;
	u64 i;

	if (unlikely(elba > dev->total_pages)) {
		pr_err("nvm: L2P data from device is out of bounds!\n");
		return -EINVAL;
	}

	for (i = 0; i < nlb; i++) {
		u64 pba = le64_to_cpu(entries[i]);


		if (unlikely(pba >= max_pages && pba != U64_MAX)) {
			pr_err("nvm: L2P data entry is out of bounds!\n");
			return -EINVAL;
		}


		if (!pba)
			continue;

		addr[i].addr = pba;
		raddr[pba].addr = slba + i;
	}

	return 0;
}
