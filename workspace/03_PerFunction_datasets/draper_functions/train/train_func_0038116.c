SVG_DetachStream(GF_BaseDecoder *plug, u16 ES_ID)
{
	SVGIn *svgin = (SVGIn *)plug->privateStack;
	if (svgin->file_name) gf_free(svgin->file_name);
	svgin->file_name = NULL;
	gf_sm_load_done(&svgin->loader);
	return GF_OK;
}
