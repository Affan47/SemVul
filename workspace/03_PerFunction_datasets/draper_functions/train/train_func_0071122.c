gpiolib_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	unsigned long flags;
	struct gpio_chip *chip = v;
	void *ret = NULL;

	spin_lock_irqsave(&gpio_lock, flags);
	if (list_is_last(&chip->list, &gpio_chips))
		ret = NULL;
	else
		ret = list_entry(chip->list.next, struct gpio_chip, list);
	spin_unlock_irqrestore(&gpio_lock, flags);

	s->private = "\n";
	++*pos;

	return ret;
}
