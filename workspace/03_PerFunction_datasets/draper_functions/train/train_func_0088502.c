go7007_boot_encoder(struct go7007 *go, int init_i2c)
{
	int ret;

	mutex_lock(&go->hw_lock);
	ret = go7007_load_encoder(go);
	mutex_unlock(&go->hw_lock);
	if (ret < 0)
		return -1;
	if (!init_i2c)
		return 0;
	if (go7007_i2c_init(go) < 0)
		return -1;
	go->i2c_adapter_online = 1;
	return 0;
}
