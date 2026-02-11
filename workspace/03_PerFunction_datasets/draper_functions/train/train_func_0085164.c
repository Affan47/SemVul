MPD_LoadMediaService(GF_MPD_In *mpdin, u32 group_index, const char *mime, const char *init_segment_name)
{
	GF_InputService *segment_ifce;
	u32 i;
    const char *sPlug;
	if (mime) {

		sPlug = gf_cfg_get_key(mpdin->service->term->user->config, "MimeTypes", mime);
		if (sPlug) sPlug = strrchr(sPlug, '"');
		if (sPlug) {
			sPlug += 2;
			segment_ifce = (GF_InputService *) gf_modules_load_interface_by_name(mpdin->service->term->user->modules, sPlug, GF_NET_CLIENT_INTERFACE);
			if (segment_ifce) {
				GF_MPDGroup *group;
				GF_SAFEALLOC(group, GF_MPDGroup);
				group->segment_ifce = segment_ifce;
				group->segment_ifce->proxy_udta = mpdin;
				group->segment_ifce->query_proxy = MPD_ClientQuery;
				gf_dash_set_group_udta(mpdin->dash, group_index, group);
				return GF_OK;
			}
		}
	}
	if (init_segment_name) {
		for (i=0; i< gf_modules_get_count(mpdin->service->term->user->modules); i++) {
			GF_InputService *ifce = (GF_InputService *) gf_modules_load_interface(mpdin->service->term->user->modules, i, GF_NET_CLIENT_INTERFACE);
			if (!ifce) continue;

			if (ifce->CanHandleURL && ifce->CanHandleURL(ifce, init_segment_name)) {
				GF_MPDGroup *group;
				GF_SAFEALLOC(group, GF_MPDGroup);
				group->segment_ifce = ifce;
				group->segment_ifce->proxy_udta = mpdin;
				group->segment_ifce->query_proxy = MPD_ClientQuery;
				gf_dash_set_group_udta(mpdin->dash, group_index, group);
				return GF_OK;
			}
			gf_modules_close_interface((GF_BaseInterface *) ifce);
		}
	}
	GF_LOG(GF_LOG_ERROR, GF_LOG_DASH, ("[MPD_IN] Error locating plugin for segment - mime type %s - name %s\n", mime, init_segment_name));
    return GF_CODEC_NOT_FOUND;
}
