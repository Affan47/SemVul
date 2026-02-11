wti_nps_destroy(StonithPlugin *s)
{
	struct pluginDevice* nps;

	if (Debug) {
		LOG(PIL_DEBUG, "%s: called.", __FUNCTION__);
	}

	VOIDERRIFWRONGDEV(s);

	nps = (struct pluginDevice *)s;

	nps->pluginid = NOTnpsid;
	if (nps->rdfd >= 0) {
		close(nps->rdfd);
		nps->rdfd = -1;
	}
	if (nps->wrfd >= 0) {
		close(nps->wrfd);
		nps->wrfd = -1;
	}
	if (nps->device != NULL) {
		FREE(nps->device);
		nps->device = NULL;
	}
	if (nps->passwd != NULL) {
		FREE(nps->passwd);
		nps->passwd = NULL;
	}
	FREE(nps);
}
