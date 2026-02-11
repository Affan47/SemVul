ms_biff_put_len_commit (BiffPut *bp)
{
	guint8 tmp[4];

	g_return_if_fail (bp != NULL);
	g_return_if_fail (bp->output != NULL);
	g_return_if_fail (bp->len_fixed == 1);
	g_return_if_fail (bp->length == 0 || bp->data);
	if (bp->version >= MS_BIFF_V8)
		XL_CHECK_CONDITION (bp->length < MAX_BIFF8_RECORD_SIZE);
	else
		XL_CHECK_CONDITION (bp->length < MAX_BIFF7_RECORD_SIZE);


	GSF_LE_SET_GUINT16 (tmp, bp->opcode);
	GSF_LE_SET_GUINT16 (tmp + 2, bp->length);
	gsf_output_write (bp->output, 4, tmp);
	gsf_output_write (bp->output, bp->length, bp->data);

	g_free (bp->data);
	bp->data      = NULL;
	bp->data_malloced = FALSE;
	bp->streamPos = gsf_output_tell (bp->output);
	bp->curpos    = 0;
}
