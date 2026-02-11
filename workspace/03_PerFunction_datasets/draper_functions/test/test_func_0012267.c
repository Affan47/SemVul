fore200e_pca_dma_unmap(struct fore200e* fore200e, u32 dma_addr, int size, int direction)
{
    DPRINTK(3, "PCI DVMA unmapping: dma_addr = 0x%08x, size = %d, direction = %d\n",
	    dma_addr, size, direction);

    dma_unmap_single(&((struct pci_dev *) fore200e->bus_dev)->dev, dma_addr, size, direction);
}
