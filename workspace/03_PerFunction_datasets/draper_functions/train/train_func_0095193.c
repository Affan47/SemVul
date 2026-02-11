dgap_get_custom_baud(struct channel_t *ch)
{
	u8 __iomem *vaddr;
	ulong offset;

	if (!ch || ch->magic != DGAP_CHANNEL_MAGIC)
		return 0;

	if (!ch->ch_bd || ch->ch_bd->magic != DGAP_BOARD_MAGIC)
		return 0;

	if (!(ch->ch_bd->bd_flags & BD_FEP5PLUS))
		return 0;

	vaddr = ch->ch_bd->re_map_membase;

	if (!vaddr)
		return 0;


	offset = (ioread16(vaddr + ECS_SEG) << 4) + (ch->ch_portnum * 0x28)
	       + LINE_SPEED;

	return readw(vaddr + offset);
}
