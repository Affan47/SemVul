fz_page_presentation(fz_document *doc, fz_page *page, float *duration)
{
	float dummy;
	if (duration)
		*duration = 0;
	else
		duration = &dummy;
	if (doc && doc->page_presentation && page)
		return doc->page_presentation(doc, page, duration);
	return NULL;
}
