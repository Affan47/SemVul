ivtv_firmware_check(struct ivtv *itv, char *where)
{
	int res = 0;


	if (ivtv_vapi(itv, CX2341X_ENC_PING_FW, 0) < 0) {
		IVTV_WARN("Encoder has died : %s\n", where);
		res = -1;
	}


	if (!res && !atomic_read(&itv->capturing) &&
	    (!atomic_read(&itv->decoding) ||
	     (atomic_read(&itv->decoding) < 2 && test_bit(IVTV_F_I_DEC_YUV,
							     &itv->i_flags)))) {

		if (ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12) < 0) {
			IVTV_WARN("Audio has died (Encoder OK) : %s\n", where);
			res = -2;
		}
	}

	if (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) {

		if (res != -2 && read_dec(0x100) != read_dec(0x104)) {

			ivtv_msleep_timeout(14, 0);
			if (read_dec(0x100) != read_dec(0x104)) {
				IVTV_WARN("Audio has died (Decoder) : %s\n",
					  where);
				res = -1;
			}
		}


		if (ivtv_vapi(itv, CX2341X_DEC_PING_FW, 0) < 0) {
			IVTV_WARN("Decoder has died : %s\n", where);
			res = -1;
		}
	}


	if (res && !atomic_read(&itv->capturing) &&
						!atomic_read(&itv->decoding)) {
		IVTV_INFO("Detected in %s that firmware had failed - "
			  "Reloading\n", where);
		res = ivtv_firmware_restart(itv);


		if (!res) {
			IVTV_INFO("Firmware restart okay\n");
			res = -EAGAIN;
		} else {
			IVTV_INFO("Firmware restart failed\n");
		}
	} else if (res) {
		res = -EIO;
	}

	return res;
}
