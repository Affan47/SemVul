qed_get_port_type(u32 media_type)
{
	int port_type;

	switch (media_type) {
	case MEDIA_SFPP_10G_FIBER:
	case MEDIA_SFP_1G_FIBER:
	case MEDIA_XFP_FIBER:
	case MEDIA_KR:
		port_type = PORT_FIBRE;
		break;
	case MEDIA_DA_TWINAX:
		port_type = PORT_DA;
		break;
	case MEDIA_BASE_T:
		port_type = PORT_TP;
		break;
	case MEDIA_NOT_PRESENT:
		port_type = PORT_NONE;
		break;
	case MEDIA_UNSPECIFIED:
	default:
		port_type = PORT_OTHER;
		break;
	}
	return port_type;
}
