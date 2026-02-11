fz_close_document(fz_document *doc)
{
	if (doc && doc->close)
		doc->close(doc);
}
