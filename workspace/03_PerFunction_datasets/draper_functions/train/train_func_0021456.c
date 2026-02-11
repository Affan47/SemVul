wil_info_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	struct net_device *ndev = wil_to_ndev(wil);
	int is_ac = power_supply_is_system_supplied();
	int rx = atomic_xchg(&wil->isr_count_rx, 0);
	int tx = atomic_xchg(&wil->isr_count_tx, 0);
	static ulong rxf_old, txf_old;
	ulong rxf = ndev->stats.rx_packets;
	ulong txf = ndev->stats.tx_packets;
	unsigned int i;


	seq_printf(s, "AC powered : %d\n", is_ac);
	seq_printf(s, "Rx irqs:packets : %8d : %8ld\n", rx, rxf - rxf_old);
	seq_printf(s, "Tx irqs:packets : %8d : %8ld\n", tx, txf - txf_old);
	rxf_old = rxf;
	txf_old = txf;

#define CHECK_QSTATE(x) (state & BIT(__QUEUE_STATE_ ## x)) ? \
	" " __stringify(x) : ""

	for (i = 0; i < ndev->num_tx_queues; i++) {
		struct netdev_queue *txq = netdev_get_tx_queue(ndev, i);
		unsigned long state = txq->state;

		seq_printf(s, "Tx queue[%i] state : 0x%lx%s%s%s\n", i, state,
			   CHECK_QSTATE(DRV_XOFF),
			   CHECK_QSTATE(STACK_XOFF),
			   CHECK_QSTATE(FROZEN)
			  );
	}
#undef CHECK_QSTATE
	return 0;
}
