tx_write_4byte_queue(struct b43_pio_txqueue *q,
				u32 ctl,
				const void *_data,
				unsigned int data_len)
{
	struct b43_wldev *dev = q->dev;
	struct b43_wl *wl = dev->wl;
	const u8 *data = _data;

	ctl |= B43_PIO8_TXCTL_0_7 | B43_PIO8_TXCTL_8_15 |
	       B43_PIO8_TXCTL_16_23 | B43_PIO8_TXCTL_24_31;
	b43_piotx_write32(q, B43_PIO8_TXCTL, ctl);

	b43_block_write(dev, data, (data_len & ~3),
			q->mmio_base + B43_PIO8_TXDATA,
			sizeof(u32));
	if (data_len & 3) {
		u8 *tail = wl->pio_tailspace;
		BUILD_BUG_ON(sizeof(wl->pio_tailspace) < 4);

		memset(tail, 0, 4);

		ctl &= ~(B43_PIO8_TXCTL_8_15 | B43_PIO8_TXCTL_16_23 |
			 B43_PIO8_TXCTL_24_31);
		switch (data_len & 3) {
		case 3:
			ctl |= B43_PIO8_TXCTL_16_23 | B43_PIO8_TXCTL_8_15;
			tail[0] = data[data_len - 3];
			tail[1] = data[data_len - 2];
			tail[2] = data[data_len - 1];
			break;
		case 2:
			ctl |= B43_PIO8_TXCTL_8_15;
			tail[0] = data[data_len - 2];
			tail[1] = data[data_len - 1];
			break;
		case 1:
			tail[0] = data[data_len - 1];
			break;
		}
		b43_piotx_write32(q, B43_PIO8_TXCTL, ctl);
		b43_block_write(dev, tail, 4,
				q->mmio_base + B43_PIO8_TXDATA,
				sizeof(u32));
	}

	return ctl;
}
