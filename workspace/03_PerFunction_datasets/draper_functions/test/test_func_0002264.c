snd_mixart_free(struct mixart_mgr *mgr)
{
	unsigned int i;

	for (i = 0; i < mgr->num_cards; i++) {
		if (mgr->chip[i])
			snd_card_free(mgr->chip[i]->card);
	}


	snd_mixart_exit_mailbox(mgr);


	if (mgr->irq >= 0)
		free_irq(mgr->irq, mgr);


	if(mgr->dsp_loaded) {
		snd_mixart_reset_board(mgr);
		dev_dbg(&mgr->pci->dev, "reset miXart !\n");
	}


	for (i = 0; i < 2; ++i)
		iounmap(mgr->mem[i].virt);

	pci_release_regions(mgr->pci);


	if(mgr->flowinfo.area) {
		snd_dma_free_pages(&mgr->flowinfo);
		mgr->flowinfo.area = NULL;
	}

	if(mgr->bufferinfo.area) {
		snd_dma_free_pages(&mgr->bufferinfo);
		mgr->bufferinfo.area = NULL;
	}

	pci_disable_device(mgr->pci);
	kfree(mgr);
	return 0;
}
