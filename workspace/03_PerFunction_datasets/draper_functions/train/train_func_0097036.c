mantis_stream_control(struct mantis_pci *mantis, enum mantis_stream_control stream_ctl)
{
	u32 reg;

	reg = mmread(MANTIS_CONTROL);
	switch (stream_ctl) {
	case STREAM_TO_HIF:
		dprintk(MANTIS_DEBUG, 1, "Set stream to HIF");
		reg &= 0xff - MANTIS_BYPASS;
		mmwrite(reg, MANTIS_CONTROL);
		reg |= MANTIS_BYPASS;
		mmwrite(reg, MANTIS_CONTROL);
		break;

	case STREAM_TO_CAM:
		dprintk(MANTIS_DEBUG, 1, "Set stream to CAM");
		reg |= MANTIS_BYPASS;
		mmwrite(reg, MANTIS_CONTROL);
		reg &= 0xff - MANTIS_BYPASS;
		mmwrite(reg, MANTIS_CONTROL);
		break;
	default:
		dprintk(MANTIS_ERROR, 1, "Unknown MODE <%02x>", stream_ctl);
		return -1;
	}

	return 0;
}
