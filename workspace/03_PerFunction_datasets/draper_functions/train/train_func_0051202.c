gda_postgres_blob_op_get_id (GdaPostgresBlobOp *pgop)
{
	g_return_val_if_fail (GDA_IS_POSTGRES_BLOB_OP (pgop), NULL);
	g_return_val_if_fail (pgop->priv, NULL);

	if (pgop->priv->blobid == InvalidOid)
		return NULL;
	else
		return g_strdup_printf ("%d", pgop->priv->blobid);
}
