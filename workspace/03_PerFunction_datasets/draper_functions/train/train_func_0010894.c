ace_tasklet(unsigned long arg)
{
	struct net_device *dev = (struct net_device *) arg;
	struct ace_private *ap = netdev_priv(dev);
	int cur_size;

	cur_size = atomic_read(&ap->cur_rx_bufs);
	if ((cur_size < RX_LOW_STD_THRES) &&
	    !test_and_set_bit(0, &ap->std_refill_busy)) {
#ifdef DEBUG
		printk("refilling buffers (current %i)\n", cur_size);
#endif
		ace_load_std_rx_ring(dev, RX_RING_SIZE - cur_size);
	}

	if (ap->version >= 2) {
		cur_size = atomic_read(&ap->cur_mini_bufs);
		if ((cur_size < RX_LOW_MINI_THRES) &&
		    !test_and_set_bit(0, &ap->mini_refill_busy)) {
#ifdef DEBUG
			printk("refilling mini buffers (current %i)\n",
			       cur_size);
#endif
			ace_load_mini_rx_ring(dev, RX_MINI_SIZE - cur_size);
		}
	}

	cur_size = atomic_read(&ap->cur_jumbo_bufs);
	if (ap->jumbo && (cur_size < RX_LOW_JUMBO_THRES) &&
	    !test_and_set_bit(0, &ap->jumbo_refill_busy)) {
#ifdef DEBUG
		printk("refilling jumbo buffers (current %i)\n", cur_size);
#endif
		ace_load_jumbo_rx_ring(dev, RX_JUMBO_SIZE - cur_size);
	}
	ap->tasklet_pending = 0;
}
