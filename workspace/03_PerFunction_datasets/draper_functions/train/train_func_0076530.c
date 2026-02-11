hs_preauth_cb(GIOChannel *chan, GIOCondition cond,
							gpointer user_data)
{
	struct audio_device *device = user_data;

	DBG("Headset disconnected during authorization");

	audio_device_cancel_authorization(device, headset_auth_cb, device);

	headset_set_state(device, HEADSET_STATE_DISCONNECTED);

	device->hs_preauth_id = 0;

	return FALSE;
}
