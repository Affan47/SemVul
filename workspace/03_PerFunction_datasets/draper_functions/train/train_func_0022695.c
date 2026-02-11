RegisterComponents() {

	gps_proto_ref =
		globalreg->kisnetserver->RegisterProtocol("GPS", 0, 0, GPS_fields_text,
												  &Protocol_GPS, NULL, this);


	_PCM(PACK_COMP_GPS) =
		globalreg->packetchain->RegisterPacketComponent("gps");
	globalreg->packetchain->RegisterHandler(&kis_gpspack_hook, this,
											CHAINPOS_POSTCAP, -100);

	return 1;
}
