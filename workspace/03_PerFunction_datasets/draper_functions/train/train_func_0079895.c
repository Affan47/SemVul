restart_bfa(struct bfad_s *bfad)
{
	unsigned long flags;
	struct pci_dev *pdev = bfad->pcidev;

	bfa_attach(&bfad->bfa, bfad, &bfad->ioc_cfg,
		   &bfad->meminfo, &bfad->hal_pcidev);


	if (bfad_setup_intr(bfad)) {
		dev_printk(KERN_WARNING, &pdev->dev,
			   "%s: bfad_setup_intr failed\n", bfad->pci_name);
		bfa_sm_send_event(bfad, BFAD_E_INIT_FAILED);
		return -1;
	}

	init_completion(&bfad->comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_iocfc_init(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);


	if ((bfad->bfad_flags & BFAD_MSIX_ON) &&
	    bfad_install_msix_handler(bfad))
		dev_printk(KERN_WARNING, &pdev->dev,
			   "%s: install_msix failed.\n", bfad->pci_name);

	bfad_init_timer(bfad);
	wait_for_completion(&bfad->comp);
	bfad_drv_start(bfad);

	return 0;
}
