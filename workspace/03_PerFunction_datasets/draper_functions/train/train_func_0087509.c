sata_rcar_ioread16_rep(void __iomem *reg, void *buffer, int count)
{
	u16 *ptr = buffer;

	while (count--) {
		u16 data = ioread32(reg);

		*ptr++ = data;
	}
}
