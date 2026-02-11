multi_get_connection_speed()
{
	int cspeed;
	char *connection_speed;

#ifdef _WIN32
	connection_speed = os_config_read_string(NULL, "ConnectionSpeed", "");
#else
	connection_speed = os_config_read_string(NULL, "ConnectionSpeed", "Fast");
#endif

	if ( !stricmp(connection_speed, NOX("Slow")) ) {
		cspeed = CONNECTION_SPEED_288;
	} else if ( !stricmp(connection_speed, NOX("56K")) ) {
		cspeed = CONNECTION_SPEED_56K;
	} else if ( !stricmp(connection_speed, NOX("ISDN")) ) {
		cspeed = CONNECTION_SPEED_SISDN;
	} else if ( !stricmp(connection_speed, NOX("Cable")) ) {
		cspeed = CONNECTION_SPEED_CABLE;
	} else if ( !stricmp(connection_speed, NOX("Fast")) ) {
		cspeed = CONNECTION_SPEED_T1;
	} else {
		cspeed = CONNECTION_SPEED_NONE;
	}

	return cspeed;
}
