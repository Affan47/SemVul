pcs_add_pin(struct pcs_device *pcs, unsigned offset,
		unsigned pin_pos)
{
	struct pcs_soc_data *pcs_soc = &pcs->socdata;
	struct pinctrl_pin_desc *pin;
	struct pcs_name *pn;
	int i;

	i = pcs->pins.cur;
	if (i >= pcs->desc.npins) {
		dev_err(pcs->dev, "too many pins, max %i\n",
			pcs->desc.npins);
		return -ENOMEM;
	}

	if (pcs_soc->irq_enable_mask) {
		unsigned val;

		val = pcs->read(pcs->base + offset);
		if (val & pcs_soc->irq_enable_mask) {
			dev_dbg(pcs->dev, "irq enabled at boot for pin at %lx (%x), clearing\n",
				(unsigned long)pcs->res->start + offset, val);
			val &= ~pcs_soc->irq_enable_mask;
			pcs->write(val, pcs->base + offset);
		}
	}

	pin = &pcs->pins.pa[i];
	pn = &pcs->names[i];
	sprintf(pn->name, "%lx.%u",
		(unsigned long)pcs->res->start + offset, pin_pos);
	pin->name = pn->name;
	pin->number = i;
	pcs->pins.cur++;

	return i;
}
