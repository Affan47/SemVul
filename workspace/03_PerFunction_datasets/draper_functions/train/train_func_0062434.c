tx_eager_mode(txdrv_t *tx, bool on)
{
	txdrv_t *t;

	tx_check(tx);
	g_assert(tx->upper == NULL);

	for (t = tx; t; t = t->lower) {
		if (on) {
			tx_srv_enable(t);
			t->flags |= TX_EAGER;
		} else {


			t->flags &= ~TX_EAGER;
		}
	}
}
