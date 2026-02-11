ci_check_s0_mc_reg_index(u16 in_reg, u16 *out_reg)
{
	bool result = true;

	switch(in_reg) {
	case mmMC_SEQ_RAS_TIMING:
		*out_reg = mmMC_SEQ_RAS_TIMING_LP;
		break;
	case mmMC_SEQ_DLL_STBY:
		*out_reg = mmMC_SEQ_DLL_STBY_LP;
		break;
	case mmMC_SEQ_G5PDX_CMD0:
		*out_reg = mmMC_SEQ_G5PDX_CMD0_LP;
		break;
	case mmMC_SEQ_G5PDX_CMD1:
		*out_reg = mmMC_SEQ_G5PDX_CMD1_LP;
		break;
	case mmMC_SEQ_G5PDX_CTRL:
		*out_reg = mmMC_SEQ_G5PDX_CTRL_LP;
		break;
	case mmMC_SEQ_CAS_TIMING:
		*out_reg = mmMC_SEQ_CAS_TIMING_LP;
	    break;
	case mmMC_SEQ_MISC_TIMING:
		*out_reg = mmMC_SEQ_MISC_TIMING_LP;
		break;
	case mmMC_SEQ_MISC_TIMING2:
		*out_reg = mmMC_SEQ_MISC_TIMING2_LP;
		break;
	case mmMC_SEQ_PMG_DVS_CMD:
		*out_reg = mmMC_SEQ_PMG_DVS_CMD_LP;
		break;
	case mmMC_SEQ_PMG_DVS_CTL:
		*out_reg = mmMC_SEQ_PMG_DVS_CTL_LP;
		break;
	case mmMC_SEQ_RD_CTL_D0:
		*out_reg = mmMC_SEQ_RD_CTL_D0_LP;
		break;
	case mmMC_SEQ_RD_CTL_D1:
		*out_reg = mmMC_SEQ_RD_CTL_D1_LP;
		break;
	case mmMC_SEQ_WR_CTL_D0:
		*out_reg = mmMC_SEQ_WR_CTL_D0_LP;
		break;
	case mmMC_SEQ_WR_CTL_D1:
		*out_reg = mmMC_SEQ_WR_CTL_D1_LP;
		break;
	case mmMC_PMG_CMD_EMRS:
		*out_reg = mmMC_SEQ_PMG_CMD_EMRS_LP;
		break;
	case mmMC_PMG_CMD_MRS:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS_LP;
		break;
	case mmMC_PMG_CMD_MRS1:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS1_LP;
		break;
	case mmMC_SEQ_PMG_TIMING:
		*out_reg = mmMC_SEQ_PMG_TIMING_LP;
		break;
	case mmMC_PMG_CMD_MRS2:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS2_LP;
		break;
	case mmMC_SEQ_WR_CTL_2:
		*out_reg = mmMC_SEQ_WR_CTL_2_LP;
		break;
	default:
		result = false;
		break;
	}

	return result;
}
