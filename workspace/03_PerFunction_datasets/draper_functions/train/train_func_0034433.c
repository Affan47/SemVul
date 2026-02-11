json_print_memory_stats(struct activity *a, int curr, int tab,
					unsigned long long itv)
{
	struct stats_memory
		*smc = (struct stats_memory *) a->buf[curr],
		*smp = (struct stats_memory *) a->buf[!curr];
	int sep = FALSE;

	xprintf0(tab, "\"memory\": {");

	if (DISPLAY_MEM_AMT(a->opt_flags)) {

		sep = TRUE;

		printf("\"memfree\": %lu, "
		       "\"memused\": %lu, "
		       "\"memused-percent\": %.2f, "
		       "\"buffers\": %lu, "
		       "\"cached\": %lu, "
		       "\"commit\": %lu, "
		       "\"commit-percent\": %.2f, "
		       "\"active\": %lu, "
		       "\"inactive\": %lu, "
		       "\"dirty\": %lu",
		       smc->frmkb,
		       smc->tlmkb - smc->frmkb,
		       smc->tlmkb ?
		       SP_VALUE(smc->frmkb, smc->tlmkb, smc->tlmkb) :
		       0.0,
		       smc->bufkb,
		       smc->camkb,
		       smc->comkb,
		       (smc->tlmkb + smc->tlskb) ?
		       SP_VALUE(0, smc->comkb, smc->tlmkb + smc->tlskb) :
		       0.0,
		       smc->activekb,
		       smc->inactkb,
		       smc->dirtykb);
	}

	if (DISPLAY_SWAP(a->opt_flags)) {

		if (sep) {
			printf(", ");
		}
		sep = TRUE;

		printf("\"swpfree\": %lu, "
		       "\"swpused\": %lu, "
		       "\"swpused-percent\": %.2f, "
		       "\"swpcad\": %lu, "
		       "\"swpcad-percent\": %.2f",
		       smc->frskb,
		       smc->tlskb - smc->frskb,
		       smc->tlskb ?
		       SP_VALUE(smc->frskb, smc->tlskb, smc->tlskb) :
		       0.0,
		       smc->caskb,
		       (smc->tlskb - smc->frskb) ?
		       SP_VALUE(0, smc->caskb, smc->tlskb - smc->frskb) :
		       0.0);
	}

	if (DISPLAY_MEMORY(a->opt_flags)) {

		if (sep) {
			printf(", ");
		}

		printf("\"frmpg\": %.2f, "
		       "\"bufpg\": %.2f, "
		       "\"campg\": %.2f",
		       S_VALUE((double) KB_TO_PG(smp->frmkb),
			       (double) KB_TO_PG(smc->frmkb), itv),
		       S_VALUE((double) KB_TO_PG(smp->bufkb),
			       (double) KB_TO_PG(smc->bufkb), itv),
		       S_VALUE((double) KB_TO_PG(smp->camkb),
			       (double) KB_TO_PG(smc->camkb), itv));
	}

	printf("}");
}
