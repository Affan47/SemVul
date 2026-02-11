reset_remote(lc_callback cb, void *cb_arg)
{
	int err;
	if (cb)
		cb(LC_CB_STAGE_RESET, 0, 0, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

	if ((err = rmt->Reset(COMMAND_RESET_DEVICE)))
		return err;

	if (cb)
		cb(LC_CB_STAGE_RESET, 1, 1, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

	deinit_concord();
	for (int i = 0; i < MAX_WAIT_FOR_BOOT; i++) {
		sleep(WAIT_FOR_BOOT_SLEEP);
		err = init_concord();
		if (err == 0) {
			err = _get_identity(NULL, NULL, 0);


			if ((err == 0) || (err == LC_ERROR_INVALID_CONFIG)) {
				err = 0;
				break;
			}
			deinit_concord();
		}
	}

	if (err != 0)
		return err;

	if (cb)
		cb(LC_CB_STAGE_RESET, 2, 2, 2, LC_CB_COUNTER_TYPE_STEPS, cb_arg,
			NULL);

	return 0;
}
