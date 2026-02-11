closexref(void)
{
	int i;
	if (xref)
	{
		pdf_close_document(xref);
		xref = NULL;
	}

	if (dim)
	{
		for (i = 0; i < dims; i++)
			fz_free(ctx, dim[i].u.dim.bbox);
		fz_free(ctx, dim);
		dim = NULL;
		dims = 0;
	}

	if (font)
	{
		fz_free(ctx, font);
		font = NULL;
		fonts = 0;
	}

	if (image)
	{
		fz_free(ctx, image);
		image = NULL;
		images = 0;
	}

	if (shading)
	{
		fz_free(ctx, shading);
		shading = NULL;
		shadings = 0;
	}

	if (pattern)
	{
		fz_free(ctx, pattern);
		pattern = NULL;
		patterns = 0;
	}

	if (form)
	{
		fz_free(ctx, form);
		form = NULL;
		forms = 0;
	}

	if (psobj)
	{
		fz_free(ctx, psobj);
		psobj = NULL;
		psobjs = 0;
	}
}
