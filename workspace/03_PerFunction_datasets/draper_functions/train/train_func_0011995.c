fz_open_rld(fz_stream *chain)
{
	fz_rld *state;
	fz_context *ctx = chain->ctx;

	fz_try(ctx)
	{
		state = fz_malloc_struct(ctx, fz_rld);
		state->chain = chain;
		state->run = 0;
		state->n = 0;
		state->c = 0;
	}
	fz_catch(ctx)
	{
		fz_close(chain);
		fz_rethrow(ctx);
	}

	return fz_new_stream(ctx, state, read_rld, close_rld);
}
