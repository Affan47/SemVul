bfad_install_msix_handler(struct bfad_s *bfad)
{
	int i, error = 0;

	for (i = 0; i < bfad->nvec; i++) {
		sprintf(bfad->msix_tab[i].name, "bfa-%s-%s",
				bfad->pci_name,
				((bfa_asic_id_cb(bfad->hal_pcidev.device_id)) ?
				msix_name_cb[i] : msix_name_ct[i]));

		error = request_irq(bfad->msix_tab[i].msix.vector,
				    (irq_handler_t) bfad_msix, 0,
				    bfad->msix_tab[i].name, &bfad->msix_tab[i]);
		bfa_trc(bfad, i);
		bfa_trc(bfad, bfad->msix_tab[i].msix.vector);
		if (error) {
			int	j;

			for (j = 0; j < i; j++)
				free_irq(bfad->msix_tab[j].msix.vector,
						&bfad->msix_tab[j]);

			bfad->bfad_flags &= ~BFAD_MSIX_ON;
			pci_disable_msix(bfad->pcidev);

			return 1;
		}
	}

	return 0;
}
