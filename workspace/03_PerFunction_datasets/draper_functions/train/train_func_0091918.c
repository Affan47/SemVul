idt77252_softint(struct work_struct *work)
{
	struct idt77252_dev *card =
		container_of(work, struct idt77252_dev, tqueue);
	u32 stat;
	int done;

	for (done = 1; ; done = 1) {
		stat = readl(SAR_REG_STAT) >> 16;

		if ((stat & 0x0f) < SAR_FBQ0_HIGH) {
			add_rx_skb(card, 0, SAR_FB_SIZE_0, 32);
			done = 0;
		}

		stat >>= 4;
		if ((stat & 0x0f) < SAR_FBQ1_HIGH) {
			add_rx_skb(card, 1, SAR_FB_SIZE_1, 32);
			done = 0;
		}

		stat >>= 4;
		if ((stat & 0x0f) < SAR_FBQ2_HIGH) {
			add_rx_skb(card, 2, SAR_FB_SIZE_2, 32);
			done = 0;
		}

		stat >>= 4;
		if ((stat & 0x0f) < SAR_FBQ3_HIGH) {
			add_rx_skb(card, 3, SAR_FB_SIZE_3, 32);
			done = 0;
		}

		if (done)
			break;
	}

	writel(readl(SAR_REG_CFG) | SAR_CFG_FBIE, SAR_REG_CFG);
}
