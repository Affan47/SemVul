cx231xx_do_i2c_scan(struct cx231xx *dev, int i2c_port)
{
	unsigned char buf;
	int i, rc;
	struct i2c_client client;

	if (!i2c_scan)
		return;


	dev->i2c_scan_running = true;

	memset(&client, 0, sizeof(client));
	client.adapter = cx231xx_get_i2c_adap(dev, i2c_port);

	for (i = 0; i < 128; i++) {
		client.addr = i;
		rc = i2c_master_recv(&client, &buf, 0);
		if (rc < 0)
			continue;
		dev_info(dev->dev,
			 "i2c scan: found device @ port %d addr 0x%x  [%s]\n",
			 i2c_port,
			 i << 1,
			 i2c_devs[i] ? i2c_devs[i] : "???");
	}

	dev->i2c_scan_running = false;
}
