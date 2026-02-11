init_uinput(struct avctp *session)
{
	struct audio_device *dev;
	char address[18], name[248 + 1];

	dev = manager_get_device(&session->server->src, &session->dst, FALSE);

	device_get_name(dev->btd_dev, name, sizeof(name));
	if (g_str_equal(name, "Nokia CK-20W")) {
		session->key_quirks[FORWARD_OP] |= QUIRK_NO_RELEASE;
		session->key_quirks[BACKWARD_OP] |= QUIRK_NO_RELEASE;
		session->key_quirks[PLAY_OP] |= QUIRK_NO_RELEASE;
		session->key_quirks[PAUSE_OP] |= QUIRK_NO_RELEASE;
	}

	ba2str(&session->dst, address);

	session->uinput = uinput_create(address);
	if (session->uinput < 0)
		error("AVRCP: failed to init uinput for %s", address);
	else
		DBG("AVRCP: uinput initialized for %s", address);
}
