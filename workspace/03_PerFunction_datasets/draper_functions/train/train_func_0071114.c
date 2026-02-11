brcmf_pcie_ring_mb_ring_bell(void *ctx)
{
	struct brcmf_pcie_ringbuf *ring = (struct brcmf_pcie_ringbuf *)ctx;
	struct brcmf_pciedev_info *devinfo = ring->devinfo;

	if (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		return -EIO;

	devinfo->ringbell(devinfo);

	return 0;
}
