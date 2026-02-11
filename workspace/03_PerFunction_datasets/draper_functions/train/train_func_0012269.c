init_drivers(void)
{
	int i, res;

	int output_loaded = 0;

	debug(RPT_DEBUG, "%s()", __FUNCTION__);

	for (i = 0; i < num_drivers; i++) {

		res = drivers_load_driver(drivernames[i]);
		if (res >= 0) {


			switch(res) {
			  case 0:
			  	break;
			  case 1:
			  	output_loaded = 1;
			  	break;
			  case 2:
			  	foreground_mode = 1;
			  	output_loaded = 1;
			  	break;
			}
		} else {
			report(RPT_ERR, "Could not load driver %.40s", drivernames[i]);
		}
	}


	if (output_loaded) {
		return 0;
	} else {
		report(RPT_ERR, "There is no output driver");
		return -1;
	}
}
