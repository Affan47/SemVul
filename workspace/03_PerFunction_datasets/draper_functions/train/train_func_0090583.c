rx_aal5(struct atm_vcc *vcc)
{
	struct eni_vcc *eni_vcc;
	unsigned long descr;
	unsigned long size,eff,length;
	struct sk_buff *skb;

	EVENT("rx_aal5\n",0,0);
	DPRINTK(">rx_aal5\n");
	eni_vcc = ENI_VCC(vcc);
	descr = readl(eni_vcc->recv+eni_vcc->descr*4);
	if ((descr & MID_RED_IDEN) != (MID_RED_RX_ID << MID_RED_SHIFT)) {
		rx_ident_err(vcc);
		return 1;
	}
	if (descr & (MID_RED_T | MID_RED_CRC_ERR)) {
		if (descr & MID_RED_T) {
			EVENT("empty cell (descr=0x%lx)\n",descr,0);
			DPRINTK(DEV_LABEL "(itf %d): trashing empty cell\n",
			    vcc->dev->number);
			size = 0;
		}
		else {
			static unsigned long silence = 0;

			if (time_after(jiffies, silence) || silence == 0) {
				printk(KERN_WARNING DEV_LABEL "(itf %d): "
				    "discarding PDU(s) with CRC error\n",
				    vcc->dev->number);
				silence = (jiffies+2*HZ)|1;
			}
			size = (descr & MID_RED_COUNT)*(ATM_CELL_PAYLOAD >> 2);
			EVENT("CRC error (descr=0x%lx,size=%ld)\n",descr,
			    size);
		}
		eff = length = 0;
		atomic_inc(&vcc->stats->rx_err);
	}
	else {
		size = (descr & MID_RED_COUNT)*(ATM_CELL_PAYLOAD >> 2);
		DPRINTK("size=%ld\n",size);
		length = readl(eni_vcc->recv+(((eni_vcc->descr+size-1) &
		    (eni_vcc->words-1)))*4) & 0xffff;

		if (length && length <= (size << 2)-8 && length <=
		  ATM_MAX_AAL5_PDU) eff = (length+3) >> 2;
		else {
			EVENT("bad PDU (descr=0x08%lx,length=%ld)\n",descr,
			    length);
			printk(KERN_ERR DEV_LABEL "(itf %d): bad AAL5 PDU "
			    "(VCI=%d,length=%ld,size=%ld (descr 0x%lx))\n",
			    vcc->dev->number,vcc->vci,length,size << 2,descr);
			length = eff = 0;
			atomic_inc(&vcc->stats->rx_err);
		}
	}
	skb = eff ? atm_alloc_charge(vcc,eff << 2,GFP_ATOMIC) : NULL;
	if (!skb) {
		discard(vcc,size);
		return 0;
	}
	skb_put(skb,length);
	DPRINTK("got len %ld\n",length);
	if (do_rx_dma(vcc,skb,1,size,eff)) return 1;
	eni_vcc->rxing++;
	return 0;
}
