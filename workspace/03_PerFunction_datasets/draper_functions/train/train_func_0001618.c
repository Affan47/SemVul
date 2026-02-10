tifm_7xx1_isr(int irq, void *dev_id)
{
	struct tifm_adapter *fm = dev_id;
	struct tifm_dev *sock;
	unsigned int irq_status, cnt;

	spin_lock(&fm->lock);
	irq_status = readl(fm->addr + FM_INTERRUPT_STATUS);
	if (irq_status == 0 || irq_status == (~0)) {
		spin_unlock(&fm->lock);
		return IRQ_NONE;
	}

	if (irq_status & TIFM_IRQ_ENABLE) {
		writel(TIFM_IRQ_ENABLE, fm->addr + FM_CLEAR_INTERRUPT_ENABLE);

		for (cnt = 0; cnt < fm->num_sockets; cnt++) {
			sock = fm->sockets[cnt];
			if (sock) {
				if ((irq_status >> cnt) & TIFM_IRQ_FIFOMASK(1))
					sock->data_event(sock);
				if ((irq_status >> cnt) & TIFM_IRQ_CARDMASK(1))
					sock->card_event(sock);
			}
		}

		fm->socket_change_set |= irq_status
					 & ((1 << fm->num_sockets) - 1);
	}
	writel(irq_status, fm->addr + FM_INTERRUPT_STATUS);

	if (fm->finish_me)
		complete_all(fm->finish_me);
	else if (!fm->socket_change_set)
		writel(TIFM_IRQ_ENABLE, fm->addr + FM_SET_INTERRUPT_ENABLE);
	else
		tifm_queue_work(&fm->media_switcher);

	spin_unlock(&fm->lock);
	return IRQ_HANDLED;
}
