pcs_allocate_pin_table(struct pcs_device *pcs)
{
	int mux_bytes, nr_pins, i;
	int num_pins_in_register = 0;

	mux_bytes = pcs->width / BITS_PER_BYTE;

	if (pcs->bits_per_mux) {
		pcs->bits_per_pin = fls(pcs->fmask);
		nr_pins = (pcs->size * BITS_PER_BYTE) / pcs->bits_per_pin;
		num_pins_in_register = pcs->width / pcs->bits_per_pin;
	} else {
		nr_pins = pcs->size / mux_bytes;
	}

	dev_dbg(pcs->dev, "allocating %i pins\n", nr_pins);
	pcs->pins.pa = devm_kzalloc(pcs->dev,
				sizeof(*pcs->pins.pa) * nr_pins,
				GFP_KERNEL);
	if (!pcs->pins.pa)
		return -ENOMEM;

	pcs->names = devm_kzalloc(pcs->dev,
				sizeof(struct pcs_name) * nr_pins,
				GFP_KERNEL);
	if (!pcs->names)
		return -ENOMEM;

	pcs->desc.pins = pcs->pins.pa;
	pcs->desc.npins = nr_pins;

	for (i = 0; i < pcs->desc.npins; i++) {
		unsigned offset;
		int res;
		int byte_num;
		int pin_pos = 0;

		if (pcs->bits_per_mux) {
			byte_num = (pcs->bits_per_pin * i) / BITS_PER_BYTE;
			offset = (byte_num / mux_bytes) * mux_bytes;
			pin_pos = i % num_pins_in_register;
		} else {
			offset = i * mux_bytes;
		}
		res = pcs_add_pin(pcs, offset, pin_pos);
		if (res < 0) {
			dev_err(pcs->dev, "error adding pins: %i\n", res);
			return res;
		}
	}

	return 0;
}
