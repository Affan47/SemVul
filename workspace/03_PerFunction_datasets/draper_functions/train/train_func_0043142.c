elsa_cs_config(struct pcmcia_device *link)
{
	int i;
	IsdnCard_t icard;

	dev_dbg(&link->dev, "elsa_config(0x%p)\n", link);

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	i = pcmcia_loop_config(link, elsa_cs_configcheck, NULL);
	if (i != 0)
		goto failed;

	if (!link->irq)
		goto failed;

	i = pcmcia_enable_device(link);
	if (i != 0)
		goto failed;

	icard.para[0] = link->irq;
	icard.para[1] = link->resource[0]->start;
	icard.protocol = protocol;
	icard.typ = ISDN_CTYPE_ELSA_PCMCIA;

	i = hisax_init_pcmcia(link, &(((local_info_t *)link->priv)->busy), &icard);
	if (i < 0) {
		printk(KERN_ERR "elsa_cs: failed to initialize Elsa "
		       "PCMCIA %d with %pR\n", i, link->resource[0]);
		elsa_cs_release(link);
	} else
		((local_info_t *)link->priv)->cardnr = i;

	return 0;
failed:
	elsa_cs_release(link);
	return -ENODEV;
}
