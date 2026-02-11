snd_ensoniq_free(struct ensoniq *ensoniq)
{
	snd_ensoniq_free_gameport(ensoniq);
	if (ensoniq->irq < 0)
		goto __hw_end;
#ifdef CHIP1370
	outl(ES_1370_SERR_DISABLE, ES_REG(ensoniq, CONTROL));
	outl(0, ES_REG(ensoniq, SERIAL));
#else
	outl(0, ES_REG(ensoniq, CONTROL));
	outl(0, ES_REG(ensoniq, SERIAL));
#endif
	if (ensoniq->irq >= 0)
		synchronize_irq(ensoniq->irq);
	pci_set_power_state(ensoniq->pci, PCI_D3hot);
      __hw_end:
#ifdef CHIP1370
	if (ensoniq->dma_bug.area)
		snd_dma_free_pages(&ensoniq->dma_bug);
#endif
	if (ensoniq->irq >= 0)
		free_irq(ensoniq->irq, ensoniq);
	pci_release_regions(ensoniq->pci);
	pci_disable_device(ensoniq->pci);
	kfree(ensoniq);
	return 0;
}
