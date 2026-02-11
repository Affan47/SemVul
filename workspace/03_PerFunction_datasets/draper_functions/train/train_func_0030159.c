parse_cookie(struct b43legacy_wldev *dev,
				      u16 cookie, int *slot)
{
	struct b43legacy_dma *dma = &dev->dma;
	struct b43legacy_dmaring *ring = NULL;

	switch (cookie & 0xF000) {
	case 0xA000:
		ring = dma->tx_ring0;
		break;
	case 0xB000:
		ring = dma->tx_ring1;
		break;
	case 0xC000:
		ring = dma->tx_ring2;
		break;
	case 0xD000:
		ring = dma->tx_ring3;
		break;
	case 0xE000:
		ring = dma->tx_ring4;
		break;
	case 0xF000:
		ring = dma->tx_ring5;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	*slot = (cookie & 0x0FFF);
	B43legacy_WARN_ON(!(ring && *slot >= 0 && *slot < ring->nr_slots));

	return ring;
}
