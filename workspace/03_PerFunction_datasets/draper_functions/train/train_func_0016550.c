byt_gpio_dbg_show(struct seq_file *s, struct gpio_chip *chip)
{
	struct byt_gpio *vg = to_byt_gpio(chip);
	int i;
	u32 conf0, val, offs;

	for (i = 0; i < vg->chip.ngpio; i++) {
		const char *pull_str = NULL;
		const char *pull = NULL;
		unsigned long flags;
		const char *label;
		offs = vg->range->pins[i] * 16;

		raw_spin_lock_irqsave(&vg->lock, flags);
		conf0 = readl(vg->reg_base + offs + BYT_CONF0_REG);
		val = readl(vg->reg_base + offs + BYT_VAL_REG);
		raw_spin_unlock_irqrestore(&vg->lock, flags);

		label = gpiochip_is_requested(chip, i);
		if (!label)
			label = "Unrequested";

		switch (conf0 & BYT_PULL_ASSIGN_MASK) {
		case BYT_PULL_ASSIGN_UP:
			pull = "up";
			break;
		case BYT_PULL_ASSIGN_DOWN:
			pull = "down";
			break;
		}

		switch (conf0 & BYT_PULL_STR_MASK) {
		case BYT_PULL_STR_2K:
			pull_str = "2k";
			break;
		case BYT_PULL_STR_10K:
			pull_str = "10k";
			break;
		case BYT_PULL_STR_20K:
			pull_str = "20k";
			break;
		case BYT_PULL_STR_40K:
			pull_str = "40k";
			break;
		}

		seq_printf(s,
			   " gpio-%-3d (%-20.20s) %s %s %s pad-%-3d offset:0x%03x mux:%d %s%s%s",
			   i,
			   label,
			   val & BYT_INPUT_EN ? "  " : "in",
			   val & BYT_OUTPUT_EN ? "   " : "out",
			   val & BYT_LEVEL ? "hi" : "lo",
			   vg->range->pins[i], offs,
			   conf0 & 0x7,
			   conf0 & BYT_TRIG_NEG ? " fall" : "     ",
			   conf0 & BYT_TRIG_POS ? " rise" : "     ",
			   conf0 & BYT_TRIG_LVL ? " level" : "      ");

		if (pull && pull_str)
			seq_printf(s, " %-4s %-3s", pull, pull_str);
		else
			seq_puts(s, "          ");

		if (conf0 & BYT_IODEN)
			seq_puts(s, " open-drain");

		seq_puts(s, "\n");
	}
}
