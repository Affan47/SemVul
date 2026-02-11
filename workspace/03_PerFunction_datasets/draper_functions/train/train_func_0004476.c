parse_da(fz_context *ctx, char *da, da_info *di)
{
	float stack[32];
	int top = 0;
	int tok;
	char *name = NULL;
	pdf_lexbuf lbuf;
	fz_stream *str = fz_open_memory(ctx, (unsigned char *)da, strlen(da));

	pdf_lexbuf_init(ctx, &lbuf, PDF_LEXBUF_SMALL);

	fz_var(str);
	fz_var(name);
	fz_try(ctx)
	{
		for (tok = pdf_lex(str, &lbuf); tok != PDF_TOK_EOF; tok = pdf_lex(str, &lbuf))
		{
			switch (tok)
			{
			case PDF_TOK_NAME:
				fz_free(ctx, name);
				name = fz_strdup(ctx, lbuf.scratch);
				break;

			case PDF_TOK_INT:
				da_check_stack(stack, &top);
				stack[top] = lbuf.i;
				top ++;
				break;

			case PDF_TOK_REAL:
				da_check_stack(stack, &top);
				stack[top] = lbuf.f;
				top ++;
				break;

			case PDF_TOK_KEYWORD:
				if (!strcmp(lbuf.scratch, "Tf"))
				{
					di->font_size = stack[0];
					di->font_name = name;
					name = NULL;
				}
				else if (!strcmp(lbuf.scratch, "rg"))
				{
					di->col[0] = stack[0];
					di->col[1] = stack[1];
					di->col[2] = stack[2];
					di->col_size = 3;
				}

				fz_free(ctx, name);
				name = NULL;
				top = 0;
				break;
			}
		}
	}
	fz_always(ctx)
	{
		fz_free(ctx, name);
		fz_close(str);
		pdf_lexbuf_fin(&lbuf);
	}
	fz_catch(ctx)
	{
		fz_rethrow(ctx);
	}
}
