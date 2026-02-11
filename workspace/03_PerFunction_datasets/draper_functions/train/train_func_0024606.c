close_rx(struct atm_vcc *vcc)
{
	struct zatm_dev *zatm_dev;
	struct zatm_vcc *zatm_vcc;
	unsigned long flags;
	int pos,shift;

	zatm_vcc = ZATM_VCC(vcc);
	zatm_dev = ZATM_DEV(vcc->dev);
	if (!zatm_vcc->rx_chan) return;
	DPRINTK("close_rx\n");

	if (vcc->vpi != ATM_VPI_UNSPEC && vcc->vci != ATM_VCI_UNSPEC) {
		spin_lock_irqsave(&zatm_dev->lock, flags);
		pos = vcc->vci >> 1;
		shift = (1-(vcc->vci & 1)) << 4;
		zpokel(zatm_dev,zpeekl(zatm_dev,pos) & ~(0xffff << shift),pos);
		zwait;
		zout(uPD98401_NOP,CMR);
		zwait;
		zout(uPD98401_NOP,CMR);
		spin_unlock_irqrestore(&zatm_dev->lock, flags);
	}
	spin_lock_irqsave(&zatm_dev->lock, flags);
	zwait;
	zout(uPD98401_DEACT_CHAN | uPD98401_CHAN_RT | (zatm_vcc->rx_chan <<
	    uPD98401_CHAN_ADDR_SHIFT),CMR);
	zwait;
	udelay(10);
	zout(uPD98401_CLOSE_CHAN | uPD98401_CHAN_RT | (zatm_vcc->rx_chan <<
	    uPD98401_CHAN_ADDR_SHIFT),CMR);
	zwait;
	if (!(zin(CMR) & uPD98401_CHAN_ADDR))
		printk(KERN_CRIT DEV_LABEL "(itf %d): can't close RX channel "
		    "%d\n",vcc->dev->number,zatm_vcc->rx_chan);
	spin_unlock_irqrestore(&zatm_dev->lock, flags);
	zatm_dev->rx_map[zatm_vcc->rx_chan] = NULL;
	zatm_vcc->rx_chan = 0;
	unuse_pool(vcc->dev,zatm_vcc->pool);
}
