t4vf_sge_stop(struct adapter *adapter)
{
	struct sge *s = &adapter->sge;

	if (s->rx_timer.function)
		del_timer_sync(&s->rx_timer);
	if (s->tx_timer.function)
		del_timer_sync(&s->tx_timer);
}
