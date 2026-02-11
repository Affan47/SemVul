neo_parse_lsr(struct jsm_board *brd, u32 port)
{
	struct jsm_channel *ch;
	int linestatus;
	unsigned long lock_flags;

	if (!brd)
		return;

	if (port >= brd->maxports)
		return;

	ch = brd->channels[port];
	if (!ch)
		return;

	linestatus = readb(&ch->ch_neo_uart->lsr);

	jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d port: %d linestatus: %x\n",
		__FILE__, __LINE__, port, linestatus);

	ch->ch_cached_lsr |= linestatus;

	if (ch->ch_cached_lsr & UART_LSR_DR) {

		neo_copy_data_from_uart_to_queue(ch);
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		jsm_check_queue_flow_control(ch);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
	}


	if (linestatus & UART_17158_RX_FIFO_DATA_ERROR)
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d Got an RX error, need to parse LSR\n",
			__FILE__, __LINE__, port);


	if (linestatus & UART_LSR_PE) {
		ch->ch_err_parity++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. PAR ERR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_FE) {
		ch->ch_err_frame++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. FRM ERR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_BI) {
		ch->ch_err_break++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. BRK INTR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_OE) {


		ch->ch_err_overrun++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. Rx Overrun!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_THRE) {
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);


		neo_copy_data_from_queue_to_uart(ch);
	}
	else if (linestatus & UART_17158_TX_AND_FIFO_CLR) {
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);


		neo_copy_data_from_queue_to_uart(ch);
	}
}
