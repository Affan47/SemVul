tx_take (amb_dev * dev) {
  amb_txq * txq = &dev->txq;
  unsigned long flags;

  PRINTD (DBG_FLOW|DBG_TX, "tx_take %p", dev);

  spin_lock_irqsave (&txq->lock, flags);

  if (txq->pending && txq->out.ptr->handle) {

    tx_complete (dev, txq->out.ptr);

    txq->out.ptr->handle = 0;

    txq->pending--;
    txq->out.ptr = NEXTQ (txq->out.ptr, txq->out.start, txq->out.limit);

    spin_unlock_irqrestore (&txq->lock, flags);
    return 0;
  } else {

    spin_unlock_irqrestore (&txq->lock, flags);
    return -1;
  }
}
