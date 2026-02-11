iwl_mvm_get_shared_mem_conf(struct iwl_mvm *mvm)
{
	struct iwl_host_cmd cmd = {
		.id = SHARED_MEM_CFG,
		.flags = CMD_WANT_SKB,
		.data = { NULL, },
		.len = { 0, },
	};
	struct iwl_rx_packet *pkt;
	struct iwl_shared_mem_cfg *mem_cfg;
	u32 i;

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON(iwl_mvm_send_cmd(mvm, &cmd)))
		return;

	pkt = cmd.resp_pkt;
	mem_cfg = (void *)pkt->data;

	mvm->shared_mem_cfg.shared_mem_addr =
		le32_to_cpu(mem_cfg->shared_mem_addr);
	mvm->shared_mem_cfg.shared_mem_size =
		le32_to_cpu(mem_cfg->shared_mem_size);
	mvm->shared_mem_cfg.sample_buff_addr =
		le32_to_cpu(mem_cfg->sample_buff_addr);
	mvm->shared_mem_cfg.sample_buff_size =
		le32_to_cpu(mem_cfg->sample_buff_size);
	mvm->shared_mem_cfg.txfifo_addr = le32_to_cpu(mem_cfg->txfifo_addr);
	for (i = 0; i < ARRAY_SIZE(mvm->shared_mem_cfg.txfifo_size); i++)
		mvm->shared_mem_cfg.txfifo_size[i] =
			le32_to_cpu(mem_cfg->txfifo_size[i]);
	for (i = 0; i < ARRAY_SIZE(mvm->shared_mem_cfg.rxfifo_size); i++)
		mvm->shared_mem_cfg.rxfifo_size[i] =
			le32_to_cpu(mem_cfg->rxfifo_size[i]);
	mvm->shared_mem_cfg.page_buff_addr =
		le32_to_cpu(mem_cfg->page_buff_addr);
	mvm->shared_mem_cfg.page_buff_size =
		le32_to_cpu(mem_cfg->page_buff_size);
	IWL_DEBUG_INFO(mvm, "SHARED MEM CFG: got memory offsets/sizes\n");

	iwl_free_resp(&cmd);
}
