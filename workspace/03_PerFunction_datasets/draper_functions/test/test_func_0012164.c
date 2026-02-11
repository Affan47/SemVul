kv_init(FILE *fh)
{

	struct writer *result;
	struct kv_writer_private *priv;

	if ((priv = malloc(sizeof(*priv))) == NULL)
		fatal(NULL, NULL);

	priv->fh = fh;
	priv->prefix = strdup("");

	if ((result = malloc(sizeof(struct writer))) == NULL)
		fatal(NULL, NULL);

	result->priv  = priv;
	result->start = kv_start;
	result->attr  = kv_attr;
	result->data  = kv_data;
	result->end   = kv_end;
	result->finish= kv_finish;

	return result;
}
