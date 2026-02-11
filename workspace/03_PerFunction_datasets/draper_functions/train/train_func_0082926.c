__irq_do_set_handler(struct irq_desc *desc, irq_flow_handler_t handle,
		     int is_chained, const char *name)
{
	if (!handle) {
		handle = handle_bad_irq;
	} else {
		struct irq_data *irq_data = &desc->irq_data;
#ifdef CONFIG_IRQ_DOMAIN_HIERARCHY


		while (irq_data) {
			if (irq_data->chip != &no_irq_chip)
				break;


			if (WARN_ON(is_chained))
				return;

			irq_data = irq_data->parent_data;
		}
#endif
		if (WARN_ON(!irq_data || irq_data->chip == &no_irq_chip))
			return;
	}


	if (handle == handle_bad_irq) {
		if (desc->irq_data.chip != &no_irq_chip)
			mask_ack_irq(desc);
		irq_state_set_disabled(desc);
		if (is_chained)
			desc->action = NULL;
		desc->depth = 1;
	}
	desc->handle_irq = handle;
	desc->name = name;

	if (handle != handle_bad_irq && is_chained) {
		irq_settings_set_noprobe(desc);
		irq_settings_set_norequest(desc);
		irq_settings_set_nothread(desc);
		desc->action = &chained_action;
		irq_startup(desc, true);
	}
}
