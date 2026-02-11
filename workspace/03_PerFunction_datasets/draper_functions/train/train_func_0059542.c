t4_alloc_mac_filt(struct adapter *adap, unsigned int mbox,
		      unsigned int viid, bool free, unsigned int naddr,
		      const u8 **addr, u16 *idx, u64 *hash, bool sleep_ok)
{
	int offset, ret = 0;
	struct fw_vi_mac_cmd c;
	unsigned int nfilters = 0;
	unsigned int max_naddr = adap->params.arch.mps_tcam_size;
	unsigned int rem = naddr;

	if (naddr > max_naddr)
		return -EINVAL;

	for (offset = 0; offset < naddr ; ) {
		unsigned int fw_naddr = (rem < ARRAY_SIZE(c.u.exact) ?
					 rem : ARRAY_SIZE(c.u.exact));
		size_t len16 = DIV_ROUND_UP(offsetof(struct fw_vi_mac_cmd,
						     u.exact[fw_naddr]), 16);
		struct fw_vi_mac_exact *p;
		int i;

		memset(&c, 0, sizeof(c));
		c.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_MAC_CMD) |
					   FW_CMD_REQUEST_F |
					   FW_CMD_WRITE_F |
					   FW_CMD_EXEC_V(free) |
					   FW_VI_MAC_CMD_VIID_V(viid));
		c.freemacs_to_len16 =
			cpu_to_be32(FW_VI_MAC_CMD_FREEMACS_V(free) |
				    FW_CMD_LEN16_V(len16));

		for (i = 0, p = c.u.exact; i < fw_naddr; i++, p++) {
			p->valid_to_idx =
				cpu_to_be16(FW_VI_MAC_CMD_VALID_F |
					    FW_VI_MAC_CMD_IDX_V(
						    FW_VI_MAC_ADD_MAC));
			memcpy(p->macaddr, addr[offset + i],
			       sizeof(p->macaddr));
		}


		ret = t4_wr_mbox_meat(adap, mbox, &c, sizeof(c), &c, sleep_ok);
		if (ret && ret != -FW_ENOMEM)
			break;

		for (i = 0, p = c.u.exact; i < fw_naddr; i++, p++) {
			u16 index = FW_VI_MAC_CMD_IDX_G(
					be16_to_cpu(p->valid_to_idx));

			if (idx)
				idx[offset + i] = (index >= max_naddr ?
						   0xffff : index);
			if (index < max_naddr)
				nfilters++;
			else if (hash)
				*hash |= (1ULL <<
					  hash_mac_addr(addr[offset + i]));
		}

		free = false;
		offset += fw_naddr;
		rem -= fw_naddr;
	}

	if (ret == 0 || ret == -FW_ENOMEM)
		ret = nfilters;
	return ret;
}
