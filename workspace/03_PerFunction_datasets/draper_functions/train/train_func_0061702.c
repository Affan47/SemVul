scan_tp(int frontend_fd)
{
	struct dtv_property p[] = {
		{ .cmd = DTV_DELIVERY_SYSTEM }
	};

	struct dtv_properties cmdseq = {
		.num = 1,
		.props = p
	};

	if ((ioctl(frontend_fd, FE_GET_PROPERTY, &cmdseq)) == -1) {
		perror("FE_GET_PROPERTY failed");
		return;
	}

	switch(p[0].u.data)
	{
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_DVBC_ANNEX_AC:
	case SYS_DVBC_ANNEX_B:
	case SYS_DVBT:
	case SYS_DSS:
		scan_tp_dvb();
		break;

	case SYS_ATSC:
		scan_tp_atsc();
		break;

	default:
		break;
	}
}
