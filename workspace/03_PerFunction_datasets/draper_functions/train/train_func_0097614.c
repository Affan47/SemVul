fm10k_iov_supported_xcast_mode_pf(struct fm10k_vf_info *vf_info,
					    u8 mode)
{
	u8 vf_flags = vf_info->vf_flags;


	switch (mode) {
	case FM10K_XCAST_MODE_PROMISC:
		if (vf_flags & FM10K_VF_FLAG_PROMISC_CAPABLE)
			return FM10K_XCAST_MODE_PROMISC;

	case FM10K_XCAST_MODE_ALLMULTI:
		if (vf_flags & FM10K_VF_FLAG_ALLMULTI_CAPABLE)
			return FM10K_XCAST_MODE_ALLMULTI;

	case FM10K_XCAST_MODE_MULTI:
		if (vf_flags & FM10K_VF_FLAG_MULTI_CAPABLE)
			return FM10K_XCAST_MODE_MULTI;

	case FM10K_XCAST_MODE_NONE:
		if (vf_flags & FM10K_VF_FLAG_NONE_CAPABLE)
			return FM10K_XCAST_MODE_NONE;

	default:
		break;
	}


	return FM10K_XCAST_MODE_DISABLE;
}
