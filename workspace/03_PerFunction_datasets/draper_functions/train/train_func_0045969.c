select_drm(struct wiimote_data *wdata)
{
	__u8 ir = wdata->state.flags & WIIPROTO_FLAGS_IR;
	bool ext;

	ext = (wdata->state.flags & WIIPROTO_FLAG_EXT_USED) ||
	      (wdata->state.flags & WIIPROTO_FLAG_MP_USED);


	if (wdata->state.devtype == WIIMOTE_DEV_BALANCE_BOARD) {
		if (ext)
			return WIIPROTO_REQ_DRM_KEE;
		else
			return WIIPROTO_REQ_DRM_K;
	}

	if (ir == WIIPROTO_FLAG_IR_BASIC) {
		if (wdata->state.flags & WIIPROTO_FLAG_ACCEL) {


			return WIIPROTO_REQ_DRM_KAIE;
		} else {
			return WIIPROTO_REQ_DRM_KIE;
		}
	} else if (ir == WIIPROTO_FLAG_IR_EXT) {
		return WIIPROTO_REQ_DRM_KAI;
	} else if (ir == WIIPROTO_FLAG_IR_FULL) {
		return WIIPROTO_REQ_DRM_SKAI1;
	} else {
		if (wdata->state.flags & WIIPROTO_FLAG_ACCEL) {
			if (ext)
				return WIIPROTO_REQ_DRM_KAE;
			else
				return WIIPROTO_REQ_DRM_KA;
		} else {
			if (ext)
				return WIIPROTO_REQ_DRM_KEE;
			else
				return WIIPROTO_REQ_DRM_K;
		}
	}
}
