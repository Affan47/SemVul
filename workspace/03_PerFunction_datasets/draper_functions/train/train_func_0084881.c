brcmf_pcie_init_scratchbuffers(struct brcmf_pciedev_info *devinfo)
{
	u64 address;
	u32 addr;

	devinfo->shared.scratch = dma_alloc_coherent(&devinfo->pdev->dev,
		BRCMF_DMA_D2H_SCRATCH_BUF_LEN,
		&devinfo->shared.scratch_dmahandle, GFP_KERNEL);
	if (!devinfo->shared.scratch)
		goto fail;

	memset(devinfo->shared.scratch, 0, BRCMF_DMA_D2H_SCRATCH_BUF_LEN);

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_ADDR_OFFSET;
	address = (u64)devinfo->shared.scratch_dmahandle;
	brcmf_pcie_write_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_write_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_LEN_OFFSET;
	brcmf_pcie_write_tcm32(devinfo, addr, BRCMF_DMA_D2H_SCRATCH_BUF_LEN);

	devinfo->shared.ringupd = dma_alloc_coherent(&devinfo->pdev->dev,
		BRCMF_DMA_D2H_RINGUPD_BUF_LEN,
		&devinfo->shared.ringupd_dmahandle, GFP_KERNEL);
	if (!devinfo->shared.ringupd)
		goto fail;

	memset(devinfo->shared.ringupd, 0, BRCMF_DMA_D2H_RINGUPD_BUF_LEN);

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_ADDR_OFFSET;
	address = (u64)devinfo->shared.ringupd_dmahandle;
	brcmf_pcie_write_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_write_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_LEN_OFFSET;
	brcmf_pcie_write_tcm32(devinfo, addr, BRCMF_DMA_D2H_RINGUPD_BUF_LEN);
	return 0;

fail:
	brcmf_err("Allocating scratch buffers failed\n");
	brcmf_pcie_release_scratchbuffers(devinfo);
	return -ENOMEM;
}
