gf_mo_update_caps(GF_MediaObject *mo)
{
	GF_CodecCapability cap;

	mo->flags &= ~GF_MO_IS_INIT;

	if (mo->type == GF_MEDIA_OBJECT_VIDEO) {
		cap.CapCode = GF_CODEC_FPS;
		gf_codec_get_capability(mo->odm->codec, &cap);
		mo->odm->codec->fps = cap.cap.valueFloat;
	}
	else if (mo->type == GF_MEDIA_OBJECT_AUDIO) {
		u32 sr, nb_ch, bps;
		sr = nb_ch = bps = 0;
		gf_mo_get_audio_info(mo, &sr, &bps, &nb_ch, NULL);
		mo->odm->codec->bytes_per_sec = sr * nb_ch * bps / 8;
	}
}
