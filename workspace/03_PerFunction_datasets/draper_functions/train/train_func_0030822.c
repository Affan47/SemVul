au0828_analog_stream_reset(struct au0828_dev *dev)
{
	dprintk(1, "au0828_analog_stream_reset called\n");
	au0828_writereg(dev, AU0828_SENSORCTRL_100, 0x0);
	mdelay(30);
	au0828_writereg(dev, AU0828_SENSORCTRL_100, 0xb3);
}
