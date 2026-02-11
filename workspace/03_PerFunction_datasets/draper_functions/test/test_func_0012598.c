speedportGetName( struct sProfile *psProfile ) {
	switch ( psProfile -> sRouterInfo.nType ) {
		case FRITZBOX_SPEEDPORT_W501V:
			return "T-Com Speedport W 501V";
		case FRITZBOX_SPEEDPORT_W701V:
			return "T-Com Speedport W 701V";
		case FRITZBOX_SPEEDPORT_W900V:
			return "T-Com Speedport W 900V";
		case FRITZBOX_SPEEDPORT_W920V:
			return "T-Com Speedport W 920V";
		default:
			break;
	}

	return NULL;
}
