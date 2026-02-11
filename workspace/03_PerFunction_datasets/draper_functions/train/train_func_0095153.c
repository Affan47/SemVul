bttv_irq_debug_low_latency(struct bttv *btv, u32 rc)
{
	pr_warn("%d: irq: skipped frame [main=%lx,o_vbi=%lx,o_field=%lx,rc=%lx]\n",
		btv->c.nr,
		(unsigned long)btv->main.dma,
		(unsigned long)le32_to_cpu(btv->main.cpu[RISC_SLOT_O_VBI+1]),
		(unsigned long)le32_to_cpu(btv->main.cpu[RISC_SLOT_O_FIELD+1]),
		(unsigned long)rc);

	if (0 == (btread(BT848_DSTATUS) & BT848_DSTATUS_HLOC)) {
		pr_notice("%d: Oh, there (temporarily?) is no input signal. "
			  "Ok, then this is harmless, don't worry ;)\n",
			  btv->c.nr);
		return;
	}
	pr_notice("%d: Uhm. Looks like we have unusual high IRQ latencies\n",
		  btv->c.nr);
	pr_notice("%d: Lets try to catch the culpit red-handed ...\n",
		  btv->c.nr);
	dump_stack();
}
