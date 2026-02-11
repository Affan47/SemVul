ramble_started(struct ramble *ramble)
{
	START_FUNC
	END_FUNC
	return (!settings_get_bool(SETTINGS_RAMBLE_BUTTON)) || ramble->started;
}
