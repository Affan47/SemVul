checkpcmciaideirq (void)
{
	if (!idedrive || pcmcia_type != PCMCIA_IDE || pcmcia_configured < 0)
		return 0;
	if (ideregs[PCMCIA_IDE_ID].ide_devcon & 2)
		return 0;
	if (idedrive[PCMCIA_IDE_ID * 2]->irq)
		return GAYLE_IRQ_BSY;
	return 0;
}
