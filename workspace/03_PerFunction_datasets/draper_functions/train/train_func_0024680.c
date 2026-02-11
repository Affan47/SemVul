gf_mo_set_position(GF_MediaObject *mo, GF_Window *src, GF_Window *dst)
{
	GF_Err e;
	GF_PrivateMediaDecoder *dec;
	if (!mo->odm || !mo->odm->codec || !mo->odm->codec->decio || (mo->odm->codec->decio->InterfaceType!=GF_PRIVATE_MEDIA_DECODER_INTERFACE)) return 0;

	dec = (GF_PrivateMediaDecoder*)mo->odm->codec->decio;
	e = dec->Control(dec, 0, src, dst);
	if (e==GF_BUFFER_TOO_SMALL) return 1;
	return 0;
}
