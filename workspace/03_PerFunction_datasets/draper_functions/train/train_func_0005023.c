gda_capi_blob_op_write (GdaBlobOp *op, GdaBlob *blob, G_GNUC_UNUSED glong offset)
{
	GdaCapiBlobOp *bop;
	GdaBinary *bin = NULL;
	glong nbwritten = -1;

	g_return_val_if_fail (GDA_IS_CAPI_BLOB_OP (op), -1);
	bop = GDA_CAPI_BLOB_OP (op);
	g_return_val_if_fail (bop->priv, -1);
	g_return_val_if_fail (GDA_IS_CONNECTION (bop->priv->cnc), -1);
	g_return_val_if_fail (blob, -1);

	if (blob->op && (blob->op != op)) {

		#define buf_size 16384
		gint nread = 0;
		GdaBlob *tmpblob = g_new0 (GdaBlob, 1);
		gda_blob_set_op (tmpblob, blob->op);

		nbwritten = 0;

		for (nread = gda_blob_op_read (tmpblob->op, tmpblob, nbwritten, buf_size);
		     nread > 0;
		     nread = gda_blob_op_read (tmpblob->op, tmpblob, nbwritten, buf_size)) {
			glong tmp_written;

			tmp_written = -1; TO_IMPLEMENT;

			if (tmp_written < 0) {

				gda_blob_free ((gpointer) tmpblob);
				return -1;
			}
			nbwritten += tmp_written;
			if (nread < buf_size)

				break;
		}
		gda_blob_free ((gpointer) tmpblob);
	}
	else {

		bin = (GdaBinary *) blob;
    		g_warning("bin not used. length=%ld", bin->binary_length);
		nbwritten = -1; TO_IMPLEMENT;
	}

	return nbwritten;
}
