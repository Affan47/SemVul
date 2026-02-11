lkbde_get_dma_dev(int d)
{
    if (!VALID_DEVICE(d)) {
        return NULL;
    }

#ifdef LINUX_BDE_DMA_DEVICE_SUPPORT
    return (void *)_devices[d].dma_dev;
#else
    return (void *)_devices[d].pci_device;
#endif
}
