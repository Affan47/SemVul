altera_mbox_is_sender(struct altera_mbox *mbox)
{
	u32 reg;


	#define MBOX_MAGIC	0xA5A5AA55
	writel_relaxed(MBOX_MAGIC, mbox->mbox_base + MAILBOX_PTR_REG);
	reg = readl_relaxed(mbox->mbox_base + MAILBOX_PTR_REG);
	if (reg == MBOX_MAGIC) {

		writel_relaxed(0, mbox->mbox_base + MAILBOX_PTR_REG);
		return true;
	}
	return false;
}
