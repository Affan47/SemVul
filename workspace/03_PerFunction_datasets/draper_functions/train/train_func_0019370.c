mega_internal_dev_inquiry(adapter_t *adapter, u8 ch, u8 tgt,
		dma_addr_t buf_dma_handle)
{
	mega_passthru	*pthru;
	dma_addr_t	pthru_dma_handle;
	megacmd_t	mc;
	int		rval;
	struct pci_dev	*pdev;


	if( make_local_pdev(adapter, &pdev) != 0 ) return -1;

	pthru = pci_alloc_consistent(pdev, sizeof(mega_passthru),
			&pthru_dma_handle);

	if( pthru == NULL ) {
		free_local_pdev(pdev);
		return -1;
	}

	pthru->timeout = 2;
	pthru->ars = 1;
	pthru->reqsenselen = 14;
	pthru->islogical = 0;

	pthru->channel = (adapter->flag & BOARD_40LD) ? 0 : ch;

	pthru->target = (adapter->flag & BOARD_40LD) ? (ch << 4)|tgt : tgt;

	pthru->cdblen = 6;

	pthru->cdb[0] = INQUIRY;
	pthru->cdb[1] = 0;
	pthru->cdb[2] = 0;
	pthru->cdb[3] = 0;
	pthru->cdb[4] = 255;
	pthru->cdb[5] = 0;


	pthru->dataxferaddr = (u32)buf_dma_handle;
	pthru->dataxferlen = 256;

	memset(&mc, 0, sizeof(megacmd_t));

	mc.cmd = MEGA_MBOXCMD_PASSTHRU;
	mc.xferaddr = (u32)pthru_dma_handle;

	rval = mega_internal_command(adapter, &mc, pthru);

	pci_free_consistent(pdev, sizeof(mega_passthru), pthru,
			pthru_dma_handle);

	free_local_pdev(pdev);

	return rval;
}
