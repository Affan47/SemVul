even_odd_aa(fz_gel *gel, int *list, int xofs)
{
	int even = 0;
	int x = 0;
	int i;
	fz_aa_context *ctxaa = gel->ctx->aa;

	for (i = 0; i < gel->alen; i++)
	{
		if (!even)
			x = gel->active[i]->x;
		else
			add_span_aa(ctxaa, list, x, gel->active[i]->x, xofs);
		even = !even;
	}
}
