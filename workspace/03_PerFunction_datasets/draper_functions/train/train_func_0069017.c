com20020_release(struct pcmcia_device *link)
{
	dev_dbg(&link->dev, "com20020_release\n");
	pcmcia_disable_device(link);
}
