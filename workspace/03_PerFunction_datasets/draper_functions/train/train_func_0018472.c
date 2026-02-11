ican3_init_new_host_interface(struct ican3_dev *mod)
{
	struct ican3_new_desc desc;
	unsigned long flags;
	void __iomem *dst;
	int i;

	spin_lock_irqsave(&mod->lock, flags);


	mod->rx_num = 0;
	mod->rx_int = 0;


	ican3_set_page(mod, QUEUE_TOHOST);
	dst = mod->dpm;


	for (i = 0; i < ICAN3_NEW_BUFFERS; i++) {
		desc.control = DESC_INTERRUPT | DESC_LEN(1);
		desc.pointer = mod->free_page;


		if (i == ICAN3_NEW_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		memcpy_toio(dst, &desc, sizeof(desc));
		dst += sizeof(desc);
		mod->free_page++;
	}


	ican3_set_page(mod, QUEUE_FROMHOST_MID);
	dst = mod->dpm;


	mod->tx_num = 0;


	for (i = 0; i < ICAN3_NEW_BUFFERS; i++) {
		desc.control = DESC_VALID | DESC_LEN(1);
		desc.pointer = mod->free_page;


		if (i == ICAN3_NEW_BUFFERS - 1)
			desc.control |= DESC_WRAP;

		memcpy_toio(dst, &desc, sizeof(desc));
		dst += sizeof(desc);
		mod->free_page++;
	}


	ican3_set_page(mod, QUEUE_FROMHOST_HIGH);
	dst = mod->dpm;


	desc.control = DESC_VALID | DESC_WRAP | DESC_LEN(1);
	desc.pointer = mod->free_page;
	memcpy_toio(dst, &desc, sizeof(desc));
	mod->free_page++;


	ican3_set_page(mod, QUEUE_FROMHOST_LOW);
	dst = mod->dpm;


	desc.control = DESC_VALID | DESC_WRAP | DESC_LEN(1);
	desc.pointer = mod->free_page;
	memcpy_toio(dst, &desc, sizeof(desc));
	mod->free_page++;

	spin_unlock_irqrestore(&mod->lock, flags);
}
