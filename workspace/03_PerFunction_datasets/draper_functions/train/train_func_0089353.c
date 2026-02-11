tx_release (hrz_dev * dev) {
  clear_bit (tx_busy, &dev->flags);
  PRINTD (DBG_TX, "cleared tx_busy for dev %p", dev);
  wake_up_interruptible (&dev->tx_queue);
}
