generate_cookie(struct b43legacy_pioqueue *queue,
			   struct b43legacy_pio_txpacket *packet)
{
	u16 cookie = 0x0000;
	int packetindex;


	switch (queue->mmio_base) {
	case B43legacy_MMIO_PIO1_BASE:
		break;
	case B43legacy_MMIO_PIO2_BASE:
		cookie = 0x1000;
		break;
	case B43legacy_MMIO_PIO3_BASE:
		cookie = 0x2000;
		break;
	case B43legacy_MMIO_PIO4_BASE:
		cookie = 0x3000;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	packetindex = pio_txpacket_getindex(packet);
	B43legacy_WARN_ON(!(((u16)packetindex & 0xF000) == 0x0000));
	cookie |= (u16)packetindex;

	return cookie;
}
