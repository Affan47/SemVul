dbgdev_wave_control_set_registers(
				struct dbg_wave_control_info *wac_info,
				union SQ_CMD_BITS *in_reg_sq_cmd,
				union GRBM_GFX_INDEX_BITS *in_reg_gfx_index)
{
	int status = 0;
	union SQ_CMD_BITS reg_sq_cmd;
	union GRBM_GFX_INDEX_BITS reg_gfx_index;
	struct HsaDbgWaveMsgAMDGen2 *pMsg;

	BUG_ON(!wac_info || !in_reg_sq_cmd || !in_reg_gfx_index);

	reg_sq_cmd.u32All = 0;
	reg_gfx_index.u32All = 0;
	pMsg = &wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2;

	switch (wac_info->mode) {

	case HSA_DBG_WAVEMODE_SINGLE:


		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.simd_id = pMsg->ui32.SIMD;
		reg_sq_cmd.bits.wave_id = pMsg->ui32.WaveId;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_SINGLE;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		break;


	case HSA_DBG_WAVEMODE_BROADCAST_PROCESS:

		reg_gfx_index.bits.sh_broadcast_writes = 1;
		reg_gfx_index.bits.se_broadcast_writes = 1;
		reg_gfx_index.bits.instance_broadcast_writes = 1;

		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		break;


	case HSA_DBG_WAVEMODE_BROADCAST_PROCESS_CU:

		reg_sq_cmd.bits.check_vmid = 1;
		reg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BROADCAST;

		reg_gfx_index.bits.sh_index = pMsg->ui32.ShaderArray;
		reg_gfx_index.bits.se_index = pMsg->ui32.ShaderEngine;
		reg_gfx_index.bits.instance_index = pMsg->ui32.HSACU;

		break;

	default:
		return -EINVAL;
	}

	switch (wac_info->operand) {
	case HSA_DBG_WAVEOP_HALT:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_HALT;
		break;

	case HSA_DBG_WAVEOP_RESUME:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_RESUME;
		break;

	case HSA_DBG_WAVEOP_KILL:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_KILL;
		break;

	case HSA_DBG_WAVEOP_DEBUG:
		reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_DEBUG;
		break;

	case HSA_DBG_WAVEOP_TRAP:
		if (wac_info->trapId < MAX_TRAPID) {
			reg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_TRAP;
			reg_sq_cmd.bits.trap_id = wac_info->trapId;
		} else {
			status = -EINVAL;
		}
		break;

	default:
		status = -EINVAL;
		break;
	}

	if (status == 0) {
		*in_reg_sq_cmd = reg_sq_cmd;
		*in_reg_gfx_index = reg_gfx_index;
	}

	return status;
}
