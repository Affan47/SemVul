stmpe_dbg_show(struct seq_file *s, struct gpio_chip *gc)
{
	unsigned i;
	unsigned gpio = gc->base;

	for (i = 0; i < gc->ngpio; i++, gpio++) {
		stmpe_dbg_show_one(s, gc, i, gpio);
		seq_printf(s, "\n");
	}
}
