biff_xf_data_destroy (BiffXFData *xf)
{
	go_format_unref (xf->style_format);
	xf->style_format = NULL;

	if (xf->mstyle) {
		gnm_style_unref (xf->mstyle);
		xf->mstyle = NULL;
	}
	g_free (xf);
}
