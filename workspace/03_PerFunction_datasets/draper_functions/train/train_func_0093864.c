MPD_CanHandleURLInService(GF_InputService *plug, const char *url)
{


	GF_MPD_In *mpdin = (GF_MPD_In*) plug->priv;
	GF_LOG(GF_LOG_DEBUG, GF_LOG_DASH, ("[MPD_IN] Received Can Handle URL In Service (%p) request from terminal for %s\n", mpdin->service, url));
	if (!plug || !plug->priv) return GF_SERVICE_ERROR;
	if (gf_dash_get_url(mpdin->dash) && !strcmp(gf_dash_get_url(mpdin->dash) , url)) {
		return 1;
	} else {
		GF_MPDGroup *mudta;
		GF_InputService *segment_ifce = NULL;
		u32 i;
		for (i=0;i<gf_dash_get_group_count(mpdin->dash); i++) {
			if (!gf_dash_is_group_selected(mpdin->dash, i)) continue;

			mudta = gf_dash_get_group_udta(mpdin->dash, i);
			segment_ifce = mudta->segment_ifce;
			if (mudta && mudta->segment_ifce && mudta->segment_ifce->CanHandleURLInService) {
				return mudta->segment_ifce->CanHandleURLInService(plug, url);
			}
		}
		return 0;
	}
}
