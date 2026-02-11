qs_intr_pkt(struct ata_host *host)
{
	unsigned int handled = 0;
	u8 sFFE;
	u8 __iomem *mmio_base = qs_mmio_base(host);

	do {
		u32 sff0 = readl(mmio_base + QS_HST_SFF);
		u32 sff1 = readl(mmio_base + QS_HST_SFF + 4);
		u8 sEVLD = (sff1 >> 30) & 0x01;
		sFFE  = sff1 >> 31;

		if (sEVLD) {
			u8 sDST = sff0 >> 16;
			u8 sHST = sff1 & 0x3f;
			unsigned int port_no = (sff1 >> 8) & 0x03;
			struct ata_port *ap = host->ports[port_no];
			struct qs_port_priv *pp = ap->private_data;
			struct ata_queued_cmd *qc;

			DPRINTK("SFF=%08x%08x: sCHAN=%u sHST=%d sDST=%02x\n",
					sff1, sff0, port_no, sHST, sDST);
			handled = 1;
			if (!pp || pp->state != qs_state_pkt)
				continue;
			qc = ata_qc_from_tag(ap, ap->link.active_tag);
			if (qc && (!(qc->tf.flags & ATA_TFLAG_POLLING))) {
				switch (sHST) {
				case 0:
				case 3:
					qs_enter_reg_mode(qc->ap);
					qs_do_or_die(qc, sDST);
					break;
				default:
					break;
				}
			}
		}
	} while (!sFFE);
	return handled;
}
