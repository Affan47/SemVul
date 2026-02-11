config_read_line(struct pctx *ctx)
{
	char *read_line;
	int ret_val = 1;

	ctx->line.len = 0;
	while(true)
	{
		read_line = fgets(ctx->line.t + ctx->line.len,
		                  ctx->line_size - ctx->line.len, ctx->in_file);
		if(!read_line)
		{
			if(feof(ctx->in_file))
				ret_val = 0;
			if(ferror(ctx->in_file))
				ret_val = -1;
			break;
		}

		ctx->line.len += strlen(read_line);
		if('\n' == *(ctx->line.t + ctx->line.len - 1)) {
			*(ctx->line.t + --ctx->line.len) = '\0';
			break;
		}
		else
		{
			char *tmp_line = realloc(ctx->line.t, ctx->line_size * 2);
			if(!tmp_line) {
				ret_val = -1;
				break;
			}

			ctx->line.t = tmp_line;
			ctx->line_size *= 2;
		}
	}

	ctx->line_num++;
	return ret_val;
}
