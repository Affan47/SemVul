gda_postgres_blob_op_new (GdaConnection *cnc)
{
	GdaPostgresBlobOp *pgop;

	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);

	pgop = g_object_new (GDA_TYPE_POSTGRES_BLOB_OP, NULL);
	pgop->priv->cnc = cnc;

	return GDA_BLOB_OP (pgop);
}
