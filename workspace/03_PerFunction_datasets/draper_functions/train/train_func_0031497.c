pio_handler_process(Pio *p_pio, uint32_t ul_id)
{
	uint32_t status;
	uint32_t i;


	status = pio_get_interrupt_status(p_pio);
	status &= pio_get_interrupt_mask(p_pio);


	if (status != 0) {

		i = 0;
		while (status != 0) {

			if (gs_interrupt_sources[i].id == ul_id) {

				if ((status & gs_interrupt_sources[i].mask) != 0) {
					gs_interrupt_sources[i].handler(gs_interrupt_sources[i].id,
							gs_interrupt_sources[i].mask);
					status &= ~(gs_interrupt_sources[i].mask);
				}
			}
			i++;
		}
	}
}
