x86_64_irq_eframe_link(ulong stkref, struct bt_info *bt, FILE *ofp)
{
	ulong irq_eframe;

	irq_eframe = stkref - machdep->machspec->irq_eframe_link;

	if (x86_64_exception_frame(EFRAME_VERIFY, irq_eframe, 0, bt, ofp))
		return irq_eframe;

	if (x86_64_exception_frame(EFRAME_VERIFY, irq_eframe+8, 0, bt, ofp)) {
		machdep->machspec->irq_eframe_link -= 8;
		return (irq_eframe + 8);
	}

	return irq_eframe;
}
