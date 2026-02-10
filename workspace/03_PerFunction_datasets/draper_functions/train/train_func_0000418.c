saa7164_api_set_encoder(struct saa7164_port *port)
{
	struct saa7164_dev *dev = port->dev;
	struct tmComResEncVideoBitRate vb;
	struct tmComResEncAudioBitRate ab;
	int ret;

	dprintk(DBGLVL_ENC, "%s() unitid=0x%x\n", __func__,
		port->hwcfg.sourceid);

	if (port->encoder_params.stream_type == V4L2_MPEG_STREAM_TYPE_MPEG2_PS)
		port->encoder_profile = EU_PROFILE_PS_DVD;
	else
		port->encoder_profile = EU_PROFILE_TS_HQ;

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_PROFILE_CONTROL, sizeof(u8), &port->encoder_profile);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);


	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_PROFILE_CONTROL, sizeof(u8), &port->encoder_profile);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);


	if (port->encoder_params.bitrate_mode ==
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
		vb.ucVideoBitRateMode = EU_VIDEO_BIT_RATE_MODE_CONSTANT;
	else
		vb.ucVideoBitRateMode = EU_VIDEO_BIT_RATE_MODE_VARIABLE_PEAK;
	vb.dwVideoBitRate = port->encoder_params.bitrate;
	vb.dwVideoBitRatePeak = port->encoder_params.bitrate_peak;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_VIDEO_BIT_RATE_CONTROL,
		sizeof(struct tmComResEncVideoBitRate),
		&vb);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);


	ab.ucAudioBitRateMode = 0;
	ab.dwAudioBitRate = 384000;
	ab.dwAudioBitRatePeak = ab.dwAudioBitRate;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_AUDIO_BIT_RATE_CONTROL,
		sizeof(struct tmComResEncAudioBitRate),
		&ab);
	if (ret != SAA_OK)
		printk(KERN_ERR "%s() error, ret = 0x%x\n", __func__,
			ret);

	saa7164_api_set_aspect_ratio(port);
	saa7164_api_set_gop_size(port);

	return ret;
}
