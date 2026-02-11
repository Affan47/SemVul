smp_fetch_sc_clr_gpc0(struct proxy *px, struct session *l4, void *l7, unsigned int opt,
                      const struct arg *args, struct sample *smp, const char *kw)
{
	struct stkctr *stkctr = smp_fetch_sc_stkctr(l4, args, kw);

	if (!stkctr)
		return 0;

	smp->flags = SMP_F_VOL_TEST;
	smp->type = SMP_T_UINT;
	smp->data.uint = 0;
	if (stkctr_entry(stkctr) != NULL) {
		void *ptr = stktable_data_ptr(stkctr->table, stkctr_entry(stkctr), STKTABLE_DT_GPC0);
		if (!ptr)
			return 0;
		smp->data.uint = stktable_data_cast(ptr, gpc0);
		stktable_data_cast(ptr, gpc0) = 0;
	}
	return 1;
}
