pdf_read_new_xref(pdf_document *xref, pdf_lexbuf *buf)
{
	fz_stream *stm = NULL;
	pdf_obj *trailer = NULL;
	pdf_obj *index = NULL;
	pdf_obj *obj = NULL;
	int num, gen, stm_ofs;
	int size, w0, w1, w2;
	int t;
	fz_context *ctx = xref->ctx;

	fz_var(trailer);
	fz_var(stm);

	fz_try(ctx)
	{
		trailer = pdf_parse_ind_obj(xref, xref->file, buf, &num, &gen, &stm_ofs);
	}
	fz_catch(ctx)
	{
		fz_throw(ctx, "cannot parse compressed xref stream object");
	}

	fz_try(ctx)
	{
		obj = pdf_dict_gets(trailer, "Size");
		if (!obj)
			fz_throw(ctx, "xref stream missing Size entry (%d %d R)", num, gen);

		size = pdf_to_int(obj);
		if (size > xref->len)
			pdf_resize_xref(xref, size);

		if (num < 0 || num >= xref->len)
			fz_throw(ctx, "object id (%d %d R) out of range (0..%d)", num, gen, xref->len - 1);

		obj = pdf_dict_gets(trailer, "W");
		if (!obj)
			fz_throw(ctx, "xref stream missing W entry (%d %d R)", num, gen);
		w0 = pdf_to_int(pdf_array_get(obj, 0));
		w1 = pdf_to_int(pdf_array_get(obj, 1));
		w2 = pdf_to_int(pdf_array_get(obj, 2));

		if (w0 < 0)
			fz_warn(ctx, "xref stream objects have corrupt type");
		if (w1 < 0)
			fz_warn(ctx, "xref stream objects have corrupt offset");
		if (w2 < 0)
			fz_warn(ctx, "xref stream objects have corrupt generation");

		w0 = w0 < 0 ? 0 : w0;
		w1 = w1 < 0 ? 0 : w1;
		w2 = w2 < 0 ? 0 : w2;

		index = pdf_dict_gets(trailer, "Index");

		stm = pdf_open_stream_with_offset(xref, num, gen, trailer, stm_ofs);

		if (!index)
		{
			pdf_read_new_xref_section(xref, stm, 0, size, w0, w1, w2);
		}
		else
		{
			int n = pdf_array_len(index);
			for (t = 0; t < n; t += 2)
			{
				int i0 = pdf_to_int(pdf_array_get(index, t + 0));
				int i1 = pdf_to_int(pdf_array_get(index, t + 1));
				pdf_read_new_xref_section(xref, stm, i0, i1, w0, w1, w2);
			}
		}
	}
	fz_always(ctx)
	{
		fz_close(stm);
	}
	fz_catch(ctx)
	{
		pdf_drop_obj(trailer);
		fz_rethrow(ctx);
	}

	return trailer;
}
