null_getinfo(StonithPlugin * s, int reqtype)
{
	struct pluginDevice* nd = (struct pluginDevice*) s;
	const char *		ret;

	ERRIFWRONGDEV(s, NULL);

	switch (reqtype) {
		case ST_DEVICEID:
			ret = nd->idinfo;
			break;

		case ST_DEVICENAME:
			ret = "(nil)";
			break;

		case ST_DEVICEDESCR:
			ret = "Dummy (do-nothing) STONITH device\n"
			"FOR TESTING ONLY!";
			break;

		case ST_CONF_XML:
			ret = nullXML;
			break;

		default:
			ret = NULL;
			break;
	}
	return ret;
}
