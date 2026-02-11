xps_load_document_structure(xps_document *doc, xps_fixdoc *fixdoc)
{
	xps_part *part;
	xml_element *root;
	fz_outline *outline;

	part = xps_read_part(doc, fixdoc->outline);
	fz_try(doc->ctx)
	{
		root = xml_parse_document(doc->ctx, part->data, part->size);
	}
	fz_always(doc->ctx)
	{
		xps_free_part(doc, part);
	}
	fz_catch(doc->ctx)
	{
		fz_rethrow(doc->ctx);
	}
	if (!root)
		return NULL;

	fz_try(doc->ctx)
	{
		outline = xps_parse_document_structure(doc, root);
	}
	fz_always(doc->ctx)
	{
		xml_free_element(doc->ctx, root);
	}
	fz_catch(doc->ctx)
	{
		fz_rethrow(doc->ctx);
	}

	return outline;
}
