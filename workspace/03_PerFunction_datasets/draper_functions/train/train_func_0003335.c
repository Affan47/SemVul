rcd_serial_destroy(StonithPlugin *s)
{
	struct pluginDevice* rcd;

	VOIDERRIFWRONGDEV(s);

	rcd = (struct pluginDevice *)s;

	rcd->pluginid = NOTrcd_serialID;
	if (rcd->hostlist) {
		stonith_free_hostlist(rcd->hostlist);
		rcd->hostlist = NULL;
	}
	rcd->hostcount = -1;
	if (rcd->device) {
		FREE(rcd->device);
	}
	if (rcd->signal) {
		FREE(rcd->signal);
	}
	FREE(rcd);
}
