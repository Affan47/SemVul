free_mem(struct usb_hcd *hcd, struct isp1760_qtd *qtd)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	int i;

	if (!qtd->payload_addr)
		return;

	for (i = 0; i < BLOCKS; i++) {
		if (priv->memory_pool[i].start == qtd->payload_addr) {
			WARN_ON(priv->memory_pool[i].free);
			priv->memory_pool[i].free = 1;
			qtd->payload_addr = 0;
			return;
		}
	}

	dev_err(hcd->self.controller, "%s: Invalid pointer: %08x\n",
						__func__, qtd->payload_addr);
	WARN_ON(1);
	qtd->payload_addr = 0;
}
