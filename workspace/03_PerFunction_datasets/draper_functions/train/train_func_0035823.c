ms_biff_put_new (GsfOutput *output, MsBiffVersion version, int codepage)
{
	BiffPut *bp;

	g_return_val_if_fail (output != NULL, NULL);

	bp = g_new (BiffPut, 1);

	bp->opcode        = 0;
	bp->length        = 0;
	bp->length        = 0;
	bp->streamPos     = gsf_output_tell (output);
	bp->data_malloced = FALSE;
	bp->data          = NULL;
	bp->len_fixed     = -1;
	bp->output        = output;
	bp->version       = version;

	bp->buf_len = 2048;
	bp->buf = g_malloc (bp->buf_len);

	if (version >= MS_BIFF_V8) {
		bp->convert = g_iconv_open ("UTF-16LE", "UTF-8");
		bp->codepage = 1200;
	} else {
		bp->codepage = (codepage > 0)
			? codepage : gsf_msole_iconv_win_codepage ();
		bp->convert = gsf_msole_iconv_open_codepage_for_export (bp->codepage);
	}

	return bp;
}
