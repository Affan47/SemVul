do_s2io_delete_unicast_mc(struct s2io_nic *sp, u64 addr)
{
	int offset;
	u64 dis_addr = S2IO_DISABLE_MAC_ENTRY, tmp64;
	struct config_param *config = &sp->config;

	for (offset = 1;
	     offset < config->max_mc_addr; offset++) {
		tmp64 = do_s2io_read_unicast_mc(sp, offset);
		if (tmp64 == addr) {

			if (do_s2io_add_mac(sp, dis_addr, offset) ==  FAILURE)
				return FAILURE;

			do_s2io_store_unicast_mc(sp);
			return SUCCESS;
		}
	}
	DBG_PRINT(ERR_DBG, "MAC address 0x%llx not found in CAM\n",
		  (unsigned long long)addr);
	return FAILURE;
}
