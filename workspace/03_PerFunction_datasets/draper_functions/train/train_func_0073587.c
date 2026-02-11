MSRobustLogin(struct pluginDevice * ms)
{
	int rc = S_OOPS;
	int j = 0;

	for ( ; ; ) {
	  if (MS_connect_device(ms) == S_OK) {
		rc = MSLogin(ms);
		if( rc == S_OK ) {
			break;
	    	}
	  }
	  if ((++j) == 20) {
		break;
	  } else {
		sleep(1);
	  }
	}

	return rc;
}
