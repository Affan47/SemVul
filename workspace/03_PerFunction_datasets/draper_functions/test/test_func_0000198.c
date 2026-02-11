ulq_find_store_roots(const kuid_t *kuid, bool prioritary,
	lookup_cb_ok_t ok, lookup_cb_err_t error, void *arg)
{
	struct ulq_item *ui;
	struct ulq *uq;

	g_assert(ok);
	g_assert(error);

	uq = ulq_get(LOOKUP_STORE, DHT_VT_BINARY, prioritary);

	ui = allocate_ulq_item(LOOKUP_STORE,  kuid, NULL, error, arg);
	ui->u.fn.ok = ok;

	ulq_putq(uq, ui);
}
