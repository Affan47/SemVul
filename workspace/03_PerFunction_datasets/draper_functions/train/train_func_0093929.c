sdma_intr(int irq, void *data)
{
	struct qib_pportdata *ppd = data;
	struct qib_devdata *dd = ppd->dd;

	if ((dd->flags & (QIB_PRESENT | QIB_BADINTR)) != QIB_PRESENT)


		return IRQ_HANDLED;

	this_cpu_inc(*dd->int_counter);


	qib_write_kreg(dd, kr_intclear, ppd->hw_pidx ?
		       INT_MASK_P(SDma, 1) : INT_MASK_P(SDma, 0));
	qib_sdma_intr(ppd);

	return IRQ_HANDLED;
}
