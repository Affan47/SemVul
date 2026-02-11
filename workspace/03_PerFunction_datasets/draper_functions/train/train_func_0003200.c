gatherpageinfo(int page, int show)
{
	pdf_obj *pageobj;
	pdf_obj *pageref;
	pdf_obj *rsrc;

	pageobj = xref->page_objs[page-1];
	pageref = xref->page_refs[page-1];

	if (!pageobj)
		fz_throw(ctx, "cannot retrieve info from page %d", page);

	gatherdimensions(page, pageref, pageobj);

	rsrc = pdf_dict_gets(pageobj, "Resources");
	gatherresourceinfo(page, rsrc, show);
}
