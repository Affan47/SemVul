avma1cs_detach(struct pcmcia_device *link)
{
	dev_dbg(&link->dev, "avma1cs_detach(0x%p)\n", link);
	avma1cs_release(link);
	kfree(link->priv);
}
