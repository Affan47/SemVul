csio_hw_fw_halt(struct csio_hw *hw, uint32_t mbox, int32_t force)
{
	enum fw_retval retval = 0;


	if (mbox <= PCIE_FW_MASTER_M) {
		struct csio_mb	*mbp;

		mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
		if (!mbp) {
			CSIO_INC_STATS(hw, n_err_nomem);
			return -ENOMEM;
		}

		csio_mb_reset(hw, mbp, CSIO_MB_DEFAULT_TMO,
			      PIORSTMODE_F | PIORST_F, FW_RESET_CMD_HALT_F,
			      NULL);

		if (csio_mb_issue(hw, mbp)) {
			csio_err(hw, "Issue of RESET command failed!\n");
			mempool_free(mbp, hw->mb_mempool);
			return -EINVAL;
		}

		retval = csio_mb_fw_retval(mbp);
		mempool_free(mbp, hw->mb_mempool);
	}


	if (retval == 0 || force) {
		csio_set_reg_field(hw, CIM_BOOT_CFG_A, UPCRST_F, UPCRST_F);
		csio_set_reg_field(hw, PCIE_FW_A, PCIE_FW_HALT_F,
				   PCIE_FW_HALT_F);
	}


	return retval ? -EINVAL : 0;
}
