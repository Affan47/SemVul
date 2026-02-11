gf_media_hevc_parse_nalu(GF_BitStream *bs, HEVCState *hevc, u8 *nal_unit_type, u8 *temporal_id)
{
	u32 reserved;
	s32 slice, ret;
	HEVCSliceInfo n_state;

	slice = 0;
	memcpy(&n_state, &hevc->s_info, sizeof(HEVCSliceInfo));

	reserved = gf_bs_read_int(bs, 1);
	if (reserved) return -1;

	*nal_unit_type = n_state.nal_unit_type = gf_bs_read_int(bs, 6);
	reserved = gf_bs_read_int(bs, 6);


	*temporal_id = n_state.temporal_id = gf_bs_read_int(bs, 3);

	ret = 0;
	switch (n_state.nal_unit_type) {
	case GF_HEVC_NALU_ACCESS_UNIT:
	case GF_HEVC_NALU_END_OF_SEQ:
	case GF_HEVC_NALU_END_OF_STREAM:
		ret = 1;
		break;


	case GF_HEVC_NALU_SLICE_RADL_N:

	case GF_HEVC_NALU_SLICE_RASL_N:

		break;


	case GF_HEVC_NALU_SLICE_TRAIL_N:
	case GF_HEVC_NALU_SLICE_TRAIL_R:
	case GF_HEVC_NALU_SLICE_TSA_N:
	case GF_HEVC_NALU_SLICE_TSA_R:
	case GF_HEVC_NALU_SLICE_STSA_N:
	case GF_HEVC_NALU_SLICE_STSA_R:

	case GF_HEVC_NALU_SLICE_BLA_W_LP:
	case GF_HEVC_NALU_SLICE_BLA_W_DLP:
	case GF_HEVC_NALU_SLICE_BLA_N_LP:
	case GF_HEVC_NALU_SLICE_IDR_W_DLP:
	case GF_HEVC_NALU_SLICE_IDR_N_LP:
	case GF_HEVC_NALU_SLICE_CRA:
	case GF_HEVC_NALU_SLICE_RADL_R:
	case GF_HEVC_NALU_SLICE_RASL_R:
		slice = 1;

		ret = hevc_parse_slice_segment(bs, hevc, &n_state);
		if (ret<0) return ret;

		hevc_compute_poc(&n_state);

		ret = 0;

		if (hevc->s_info.poc != n_state.poc) {
			ret=1;
			break;
		}
		break;
	case GF_HEVC_NALU_SEQ_PARAM:
	case GF_HEVC_NALU_PIC_PARAM:
	case GF_HEVC_NALU_VID_PARAM:
		return 0;
	default:
		break;
	}


	if (ret && hevc->s_info.sps) {
		n_state.frame_num_offset_prev = hevc->s_info.frame_num_offset;
		n_state.frame_num_prev = hevc->s_info.frame_num;

		n_state.poc_lsb_prev = hevc->s_info.poc_lsb;
		n_state.poc_msb_prev = hevc->s_info.poc_msb;

	}
	if (slice) hevc_compute_poc(&n_state);
	memcpy(&hevc->s_info, &n_state, sizeof(HEVCSliceInfo));
	return ret;
}
