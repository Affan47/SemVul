RP_SetupObjects(RTPClient *rtp)
{
	GF_ObjectDescriptor *od;
	RTPStream *ch;
	u32 i;


	i=0;
	while ((ch = (RTPStream *)gf_list_enum(rtp->channels, &i))) {
		if (ch->control && !strnicmp(ch->control, "data:", 5)) continue;

		if (!rtp->media_type) {
			od = RP_GetChannelOD(ch, i);
			if (!od) continue;
			gf_term_add_media(rtp->service, (GF_Descriptor*)od, 1);
		} else if (rtp->media_type==ch->depacketizer->sl_map.StreamType) {
			od = RP_GetChannelOD(ch, i);
			if (!od) continue;
			gf_term_add_media(rtp->service, (GF_Descriptor*)od, 1);
			rtp->media_type = 0;
			break;
		}
	}
	gf_term_add_media(rtp->service, NULL, 0);
}
