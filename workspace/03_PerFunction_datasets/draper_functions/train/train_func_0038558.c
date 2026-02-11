cbz_close_document(cbz_document *doc)
{
	int i;
	fz_context *ctx = doc->ctx;
	for (i = 0; i < doc->entry_count; i++)
		fz_free(ctx, doc->entry[i].name);
	fz_free(ctx, doc->entry);
	fz_free(ctx, doc->page);
	fz_close(doc->file);
	fz_free(ctx, doc);
}
