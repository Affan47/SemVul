dvb_open_device(adapter *ad)
{
	char buf[100];
	LOG("trying to open [%d] adapter %d and frontend %d", ad->id, ad->pa,
			ad->fn);
	sprintf(buf, "/dev/dvb/adapter%d/frontend%d", ad->pa, ad->fn);
	ad->fe = open(buf, O_RDWR | O_NONBLOCK);
	sprintf(buf, "/dev/dvb/adapter%d/dvr%d", ad->pa, ad->fn);
	ad->dvr = open(buf, O_RDONLY | O_NONBLOCK);
	if (ad->fe < 0 || ad->dvr < 0)
	{
		sprintf(buf, "/dev/dvb/adapter%d/frontend%d", ad->pa, ad->fn);
		LOGL(0, "Could not open %s in RW mode (fe: %d, dvr: %d)", buf, ad->fe,
				ad->dvr);
		if (ad->fe >= 0)
			close(ad->fe);
		if (ad->dvr >= 0)
			close(ad->dvr);
		ad->fe = ad->dvr = -1;
		return 1;
	}
	ad->type = ADAPTER_DVB;
	ad->dmx = -1;
	LOG("opened DVB adapter %d fe:%d dvr:%d", ad->id, ad->fe, ad->dvr);
	if (ioctl(ad->dvr, DMX_SET_BUFFER_SIZE, opts.dvr_buffer) < 0)
		LOG("couldn't set DVR buffer size error %d: %s", errno, strerror(errno))
	else
		LOG("DVR buffer set to %d bytes", opts.dvr_buffer);

	if (ad->dmx_source >= 0)
	{
		sprintf(buf, "/dev/dvb/adapter%d/demux%d", ad->pa, ad->fn);
		ad->dmx = open(buf, O_RDWR | O_NONBLOCK);
		if (ad->dmx <= 0)
			LOG("DMX_SET_SOURCE: Failed opening %s", buf)
		else if (ioctl(ad->dmx, DMX_SET_SOURCE, &ad->dmx_source))
		{
			LOG("DMX_SET_SOURCE failed for adapter %d - %d: %s", ad->id, errno,
					strerror(errno));
		}
		else
			LOG("Set DMX_SET_SOURCE for adapter %d to %d", ad->id,
					ad->dmx_source);

	}

	return 0;
}
