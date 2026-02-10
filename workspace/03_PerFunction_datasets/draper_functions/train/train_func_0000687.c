bnx2x_dcbx_init(struct bnx2x *bp, bool update_shmem)
{
	u32 dcbx_lldp_params_offset = SHMEM_LLDP_DCBX_PARAMS_NONE;


	if ((!bp->port.pmf) && (!(bp->flags & BC_SUPPORTS_DCBX_MSG_NON_PMF)))
		return;

	if (bp->dcbx_enabled <= 0)
		return;


	DP(BNX2X_MSG_DCB, "dcb_state %d bp->port.pmf %d\n",
	   bp->dcb_state, bp->port.pmf);

	if (bp->dcb_state == BNX2X_DCB_STATE_ON &&
	    SHMEM2_HAS(bp, dcbx_lldp_params_offset)) {
		dcbx_lldp_params_offset =
			SHMEM2_RD(bp, dcbx_lldp_params_offset);

		DP(BNX2X_MSG_DCB, "dcbx_lldp_params_offset 0x%x\n",
		   dcbx_lldp_params_offset);

		bnx2x_update_drv_flags(bp, 1 << DRV_FLAGS_DCB_CONFIGURED, 0);

		if (SHMEM_LLDP_DCBX_PARAMS_NONE != dcbx_lldp_params_offset) {


			bnx2x_acquire_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
			if (update_shmem)
				bnx2x_dcbx_admin_mib_updated_params(bp,
					dcbx_lldp_params_offset);


			bnx2x_fw_command(bp,
					 DRV_MSG_CODE_DCBX_ADMIN_PMF_MSG, 0);


			bnx2x_release_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
		}
	}
}
