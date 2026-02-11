wbcir_irq_tx(struct wbcir_data *data)
{
	unsigned int space;
	unsigned int used;
	u8 bytes[16];
	u8 byte;

	if (!data->txbuf)
		return;

	switch (data->txstate) {
	case WBCIR_TXSTATE_INACTIVE:

		space = 16;
		break;
	case WBCIR_TXSTATE_ACTIVE:

		space = 13;
		break;
	case WBCIR_TXSTATE_ERROR:
		space = 0;
		break;
	default:
		return;
	}


	for (used = 0; used < space && data->txoff != data->txlen; used++) {
		if (data->txbuf[data->txoff] == 0) {
			data->txoff++;
			continue;
		}
		byte = min((u32)0x80, data->txbuf[data->txoff]);
		data->txbuf[data->txoff] -= byte;
		byte--;
		byte |= (data->txoff % 2 ? 0x80 : 0x00);
		bytes[used] = byte;
	}

	while (data->txbuf[data->txoff] == 0 && data->txoff != data->txlen)
		data->txoff++;

	if (used == 0) {

		if (data->txstate == WBCIR_TXSTATE_ERROR)

			outb(WBCIR_TX_UNDERRUN, data->sbase + WBCIR_REG_SP3_ASCR);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR);
		kfree(data->txbuf);
		data->txbuf = NULL;
		data->txstate = WBCIR_TXSTATE_INACTIVE;
	} else if (data->txoff == data->txlen) {

		outsb(data->sbase + WBCIR_REG_SP3_TXDATA, bytes, used - 1);
		outb(WBCIR_TX_EOT, data->sbase + WBCIR_REG_SP3_ASCR);
		outb(bytes[used - 1], data->sbase + WBCIR_REG_SP3_TXDATA);
		wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
				  WBCIR_IRQ_TX_EMPTY);
	} else {

		outsb(data->sbase + WBCIR_REG_SP3_RXDATA, bytes, used);
		if (data->txstate == WBCIR_TXSTATE_INACTIVE) {
			wbcir_set_irqmask(data, WBCIR_IRQ_RX | WBCIR_IRQ_ERR |
					  WBCIR_IRQ_TX_LOW);
			data->txstate = WBCIR_TXSTATE_ACTIVE;
		}
	}
}
