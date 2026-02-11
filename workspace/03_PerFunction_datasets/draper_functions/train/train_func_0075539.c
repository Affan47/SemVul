IMG_ConnectService(GF_InputService *plug, GF_ClientService *serv, const char *url)
{
	char *sExt;
	IMGLoader *read = (IMGLoader *)plug->priv;

	read->service = serv;
        if (!url)
          return GF_BAD_PARAM;
	sExt = strrchr(url, '.');
	if (!stricmp(sExt, ".jpeg") || !stricmp(sExt, ".jpg")) read->img_type = IMG_JPEG;
	else if (!stricmp(sExt, ".png")) read->img_type = IMG_PNG;
	else if (!stricmp(sExt, ".pngd")) read->img_type = IMG_PNGD;
	else if (!stricmp(sExt, ".pngds")) read->img_type = IMG_PNGDS;
	else if (!stricmp(sExt, ".pngs")) read->img_type = IMG_PNGS;
	else if (!stricmp(sExt, ".bmp")) read->img_type = IMG_BMP;

	if (read->dnload) gf_term_download_del(read->dnload);
	read->dnload = NULL;


	if (!jp_is_local(url)) {
		jp_download_file(plug, url);
		return GF_OK;
	}

	read->stream = fopen(url, "rb");
	if (read->stream) {
		gf_f64_seek(read->stream, 0, SEEK_END);
		read->data_size = (u32) gf_f64_tell(read->stream);
		gf_f64_seek(read->stream, 0, SEEK_SET);
	}
	gf_term_on_connect(serv, NULL, read->stream ? GF_OK : GF_URL_ERROR);
	if (read->stream && read->is_inline) IMG_SetupObject(read);
	return GF_OK;
}
