drm_dp_dpcd_access(struct drm_dp_aux *aux, u8 request,
			      unsigned int offset, void *buffer, size_t size)
{
	struct drm_dp_aux_msg msg;
	unsigned int retry;
	int err = 0;

	memset(&msg, 0, sizeof(msg));
	msg.address = offset;
	msg.request = request;
	msg.buffer = buffer;
	msg.size = size;

	mutex_lock(&aux->hw_mutex);


	for (retry = 0; retry < 32; retry++) {

		err = aux->transfer(aux, &msg);
		if (err < 0) {
			if (err == -EBUSY)
				continue;

			goto unlock;
		}


		switch (msg.reply & DP_AUX_NATIVE_REPLY_MASK) {
		case DP_AUX_NATIVE_REPLY_ACK:
			if (err < size)
				err = -EPROTO;
			goto unlock;

		case DP_AUX_NATIVE_REPLY_NACK:
			err = -EIO;
			goto unlock;

		case DP_AUX_NATIVE_REPLY_DEFER:
			usleep_range(AUX_RETRY_INTERVAL, AUX_RETRY_INTERVAL + 100);
			break;
		}
	}

	DRM_DEBUG_KMS("too many retries, giving up\n");
	err = -EIO;

unlock:
	mutex_unlock(&aux->hw_mutex);
	return err;
}
