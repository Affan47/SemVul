bnx2x_vf_handle_flr_event(struct bnx2x *bp)
{
	int i;


	for (i = 0; i < FLRD_VFS_DWORDS; i++)
		bp->vfdb->flrd_vfs[i] = SHMEM2_RD(bp, mcp_vf_disabled[i]);

	DP(BNX2X_MSG_MCP,
	   "DRV_STATUS_VF_DISABLED received for vfs 0x%x 0x%x\n",
	   bp->vfdb->flrd_vfs[0], bp->vfdb->flrd_vfs[1]);

	for_each_vf(bp, i) {
		struct bnx2x_virtf *vf = BP_VF(bp, i);
		u32 reset = 0;

		if (vf->abs_vfid < 32)
			reset = bp->vfdb->flrd_vfs[0] & (1 << vf->abs_vfid);
		else
			reset = bp->vfdb->flrd_vfs[1] &
				(1 << (vf->abs_vfid - 32));

		if (reset) {

			vf->state = VF_RESET;
			vf->flr_clnup_stage = true;

			DP(BNX2X_MSG_IOV,
			   "Initiating Final cleanup for VF %d\n",
			   vf->abs_vfid);
		}
	}


	bnx2x_vf_flr_clnup(bp);
}
