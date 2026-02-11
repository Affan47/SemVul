irq_gc_suspend(void)
{
	struct irq_chip_generic *gc;

	list_for_each_entry(gc, &gc_list, list) {
		struct irq_chip_type *ct = gc->chip_types;

		if (ct->chip.irq_suspend) {
			struct irq_data *data = irq_gc_get_irq_data(gc);

			if (data)
				ct->chip.irq_suspend(data);
		}

		if (gc->suspend)
			gc->suspend(gc);
	}
	return 0;
}
