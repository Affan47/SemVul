sil164_save_state(struct i2c_client *client, uint8_t *state)
{
	int i;

	for (i = 0x8; i <= 0xe; i++)
		state[i] = sil164_read(client, i);
}
