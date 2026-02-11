tg3_init_hw(struct tg3 *tp, int reset_phy)
{	DBGP("%s\n", __func__);

	tg3_switch_clocks(tp);

	tw32(TG3PCI_MEM_WIN_BASE_ADDR, 0);

	return tg3_reset_hw(tp, reset_phy);
}
