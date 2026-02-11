camel_header_references_inreplyto_decode (const gchar *in)
{
	struct _camel_header_references *ref = NULL;

	if (in == NULL || in[0] == '\0')
		return NULL;

	header_references_decode_single (&in, &ref);

	return ref;
}
