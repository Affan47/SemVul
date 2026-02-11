iwl_trans_pcie_dump_monitor(struct iwl_trans *trans,
			    struct iwl_fw_error_dump_data **data,
			    u32 monitor_len)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 len = 0;

	if ((trans_pcie->fw_mon_page &&
	     trans->cfg->device_family == IWL_DEVICE_FAMILY_7000) ||
	    trans->dbg_dest_tlv) {
		struct iwl_fw_error_dump_fw_mon *fw_mon_data;
		u32 base, write_ptr, wrap_cnt;


		if (trans->dbg_dest_tlv) {
			write_ptr =
				le32_to_cpu(trans->dbg_dest_tlv->write_ptr_reg);
			wrap_cnt = le32_to_cpu(trans->dbg_dest_tlv->wrap_count);
			base = le32_to_cpu(trans->dbg_dest_tlv->base_reg);
		} else {
			base = MON_BUFF_BASE_ADDR;
			write_ptr = MON_BUFF_WRPTR;
			wrap_cnt = MON_BUFF_CYCLE_CNT;
		}

		(*data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_FW_MONITOR);
		fw_mon_data = (void *)(*data)->data;
		fw_mon_data->fw_mon_wr_ptr =
			cpu_to_le32(iwl_read_prph(trans, write_ptr));
		fw_mon_data->fw_mon_cycle_cnt =
			cpu_to_le32(iwl_read_prph(trans, wrap_cnt));
		fw_mon_data->fw_mon_base_ptr =
			cpu_to_le32(iwl_read_prph(trans, base));

		len += sizeof(**data) + sizeof(*fw_mon_data);
		if (trans_pcie->fw_mon_page) {


			dma_sync_single_for_cpu(trans->dev,
						trans_pcie->fw_mon_phys,
						trans_pcie->fw_mon_size,
						DMA_FROM_DEVICE);
			memcpy(fw_mon_data->data,
			       page_address(trans_pcie->fw_mon_page),
			       trans_pcie->fw_mon_size);

			monitor_len = trans_pcie->fw_mon_size;
		} else if (trans->dbg_dest_tlv->monitor_mode == SMEM_MODE) {


			base = iwl_read_prph(trans, base) <<
			       trans->dbg_dest_tlv->base_shift;
			iwl_trans_read_mem(trans, base, fw_mon_data->data,
					   monitor_len / sizeof(u32));
		} else if (trans->dbg_dest_tlv->monitor_mode == MARBH_MODE) {
			monitor_len =
				iwl_trans_pci_dump_marbh_monitor(trans,
								 fw_mon_data,
								 monitor_len);
		} else {

			monitor_len = 0;
		}

		len += monitor_len;
		(*data)->len = cpu_to_le32(monitor_len + sizeof(*fw_mon_data));
	}

	return len;
}
