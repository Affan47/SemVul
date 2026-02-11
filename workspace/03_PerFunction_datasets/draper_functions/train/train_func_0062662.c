efab_irq ( struct net_device *netdev, int enable )
{
	struct efab_nic *efab = netdev_priv ( netdev );
	struct efab_ev_queue *ev_queue = &efab->ev_queue;

	switch ( enable ) {
	case 0:
		falcon_interrupts ( efab, 0, 0 );
		break;
	case 1:
		falcon_interrupts ( efab, 1, 0 );
		falcon_eventq_read_ack ( efab, ev_queue );
		break;
	case 2:
		falcon_interrupts ( efab, 1, 1 );
		break;
	}
}
