drawRange()
{
	char buf[32];


	setGaugeColor(HUD_C_BRIGHT);

	switch ( HUD_config.rp_dist ) {

	case RR_SHORT:
		renderPrintf(position[0] + Radar_dist_offsets[RR_SHORT][0], position[1] + Radar_dist_offsets[RR_SHORT][1], XSTR( "2k", 467));
		break;

	case RR_LONG:
		renderPrintf(position[0] + Radar_dist_offsets[RR_LONG][0], position[1] + Radar_dist_offsets[RR_LONG][1], XSTR( "10k", 468));
		break;

	case RR_INFINITY:
		sprintf(buf, NOX("%c"), Lcl_special_chars);
		renderPrintf(position[0] + Radar_dist_offsets[RR_INFINITY][0], position[1] + Radar_dist_offsets[RR_INFINITY][1], buf);
		break;

	default:
		Int3();
		break;
	}
}
