tda10048_firmware_upload(struct dvb_frontend *fe)
{
	struct tda10048_state *state = fe->demodulator_priv;
	struct tda10048_config *config = &state->config;
	const struct firmware *fw;
	int ret;
	int pos = 0;
	int cnt;
	u8 wlen = config->fwbulkwritelen;

	if ((wlen != TDA10048_BULKWRITE_200) && (wlen != TDA10048_BULKWRITE_50))
		wlen = TDA10048_BULKWRITE_200;


	printk(KERN_INFO "%s: waiting for firmware upload (%s)...\n",
		__func__,
		TDA10048_DEFAULT_FIRMWARE);

	ret = request_firmware(&fw, TDA10048_DEFAULT_FIRMWARE,
		state->i2c->dev.parent);
	if (ret) {
		printk(KERN_ERR "%s: Upload failed. (file not found?)\n",
			__func__);
		return -EIO;
	} else {
		printk(KERN_INFO "%s: firmware read %Zu bytes.\n",
			__func__,
			fw->size);
		ret = 0;
	}

	if (fw->size != TDA10048_DEFAULT_FIRMWARE_SIZE) {
		printk(KERN_ERR "%s: firmware incorrect size\n", __func__);
		ret = -EIO;
	} else {
		printk(KERN_INFO "%s: firmware uploading\n", __func__);


		tda10048_writereg(state, TDA10048_CONF_TRISTATE1,
			tda10048_readreg(state, TDA10048_CONF_TRISTATE1)
				& 0xfe);
		tda10048_writereg(state, TDA10048_CONF_TRISTATE1,
			tda10048_readreg(state, TDA10048_CONF_TRISTATE1)
				| 0x01);


		tda10048_writereg(state, TDA10048_CONF_C4_1,
			tda10048_readreg(state, TDA10048_CONF_C4_1) & 0xf9);


		tda10048_writereg(state, TDA10048_CONF_C4_1,
			tda10048_readreg(state, TDA10048_CONF_C4_1) | 0x08);


		tda10048_writereg(state, TDA10048_DSP_CODE_CPT, 0);


		while (pos < fw->size) {

			if ((fw->size - pos) > wlen)
				cnt = wlen;
			else
				cnt = fw->size - pos;

			tda10048_writeregbulk(state, TDA10048_DSP_CODE_IN,
				&fw->data[pos], cnt);

			pos += cnt;
		}

		ret = -EIO;

		for (cnt = 0; cnt < 250 ; cnt += 10) {

			msleep(10);

			if (tda10048_readreg(state, TDA10048_SYNC_STATUS)
				& 0x40) {
				ret = 0;
				break;
			}
		}
	}

	release_firmware(fw);

	if (ret == 0) {
		printk(KERN_INFO "%s: firmware uploaded\n", __func__);
		state->fwloaded = 1;
	} else
		printk(KERN_ERR "%s: firmware upload failed\n", __func__);

	return ret;
}
