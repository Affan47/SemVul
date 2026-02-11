tx_shutdown(txdrv_t *tx)
{
	txdrv_t *t;

	tx_check(tx);
	g_assert(tx->upper == NULL);

	for (t = tx; t; t = t->lower) {
		t->flags |= TX_DOWN;


		if (t->flags & TX_SERVICE)
			tx_srv_disable(t);

		TX_SHUTDOWN(t);
	}
}
