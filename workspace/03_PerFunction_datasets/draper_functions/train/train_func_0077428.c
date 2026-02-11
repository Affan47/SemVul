azx_clear_irq_pending(struct azx *chip)
{
	struct hdac_bus *bus = azx_bus(chip);
	struct hdac_stream *s;

	spin_lock_irq(&bus->reg_lock);
	list_for_each_entry(s, &bus->stream_list, list) {
		struct azx_dev *azx_dev = stream_to_azx_dev(s);
		azx_dev->irq_pending = 0;
	}
	spin_unlock_irq(&bus->reg_lock);
}
