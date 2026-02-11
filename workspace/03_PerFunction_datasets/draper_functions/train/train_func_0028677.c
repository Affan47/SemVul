gda_thread_recordset_fetch_next (GdaDataSelect *model, GdaRow **prow, gint rownum, GError **error)
{
	GdaThreadRecordset *rs = (GdaThreadRecordset*) model;
	ThreadData wdata;
	gboolean retval;
	guint jid;

	wdata.select = (GdaDataSelect *) rs->priv->sub_model;
	wdata.rownum = rownum;
	wdata.row = prow;
	jid = gda_thread_wrapper_execute (rs->priv->wrapper,
					  (GdaThreadWrapperFunc) sub_thread_fetch_next,
					  &wdata, NULL, NULL);
	retval = GPOINTER_TO_INT (gda_thread_wrapper_fetch_result (rs->priv->wrapper, TRUE, jid, error)) ?
		TRUE : FALSE;
	COPY_PUBLIC_DATA (rs->priv->sub_model, rs);

	if (*prow && rs->priv->blobs_conv)
		alter_blob_values (rs, prow);

	return retval;
}
