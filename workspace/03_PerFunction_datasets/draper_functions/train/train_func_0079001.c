sedlbauer_probe(struct pcmcia_device *link)
{
	local_info_t *local;

	dev_dbg(&link->dev, "sedlbauer_attach()\n");


	local = kzalloc(sizeof(local_info_t), GFP_KERNEL);
	if (!local) return -ENOMEM;
	local->cardnr = -1;

	local->p_dev = link;
	link->priv = local;

	return sedlbauer_config(link);
}
