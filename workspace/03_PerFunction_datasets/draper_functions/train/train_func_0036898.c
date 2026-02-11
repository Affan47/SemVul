pdf_cache_object(pdf_document *xref, int num, int gen)
{
	pdf_xref_entry *x;
	int rnum, rgen;
	fz_context *ctx = xref->ctx;

	if (num < 0 || num >= xref->len)
		fz_throw(ctx, "object out of range (%d %d R); xref size %d", num, gen, xref->len);

	x = &xref->table[num];

	if (x->obj)
		return;

	if (x->type == 'f')
	{
		x->obj = pdf_new_null(ctx);
		return;
	}
	else if (x->type == 'n')
	{
		fz_seek(xref->file, x->ofs, 0);

		fz_try(ctx)
		{
			x->obj = pdf_parse_ind_obj(xref, xref->file, &xref->lexbuf.base,
					&rnum, &rgen, &x->stm_ofs);
		}
		fz_catch(ctx)
		{
			fz_throw(ctx, "cannot parse object (%d %d R)", num, gen);
		}

		if (rnum != num)
		{
			pdf_drop_obj(x->obj);
			x->obj = NULL;
			fz_throw(ctx, "found object (%d %d R) instead of (%d %d R)", rnum, rgen, num, gen);
		}

		if (xref->crypt)
			pdf_crypt_obj(ctx, xref->crypt, x->obj, num, gen);
	}
	else if (x->type == 'o')
	{
		if (!x->obj)
		{
			fz_try(ctx)
			{
				pdf_load_obj_stm(xref, x->ofs, 0, &xref->lexbuf.base);
			}
			fz_catch(ctx)
			{
				fz_throw(ctx, "cannot load object stream containing object (%d %d R)", num, gen);
			}
			if (!x->obj)
				fz_throw(ctx, "object (%d %d R) was not found in its object stream", num, gen);
		}
	}
	else
	{
		fz_throw(ctx, "cannot find object in xref (%d %d R)", num, gen);
	}
}
