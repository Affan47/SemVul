pdf_free_annot(fz_context *ctx, pdf_annot *annot)
{
	pdf_annot *next;

	do
	{
		next = annot->next;
		if (annot->ap)
			pdf_drop_xobject(ctx, annot->ap);
		pdf_drop_obj(annot->obj);
		fz_free(ctx, annot);
		annot = next;
	}
	while (annot);
}
