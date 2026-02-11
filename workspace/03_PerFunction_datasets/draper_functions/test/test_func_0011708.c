nvkm_pci_new_(const struct nvkm_pci_func *func, struct nvkm_device *device,
	      int index, struct nvkm_pci **ppci)
{
	struct nvkm_pci *pci;

	if (!(pci = *ppci = kzalloc(sizeof(**ppci), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_subdev_ctor(&nvkm_pci_func, device, index, 0, &pci->subdev);
	pci->func = func;
	pci->pdev = device->func->pci(device)->pdev;
	pci->irq = -1;

	if (device->type == NVKM_DEVICE_AGP)
		nvkm_agp_ctor(pci);

	switch (pci->pdev->device & 0x0ff0) {
	case 0x00f0:
	case 0x02e0:

		break;
	default:
		switch (device->chipset) {
		case 0xaa:

			break;
		default:
			pci->msi = true;
			break;
		}
	}

#ifdef __BIG_ENDIAN
	pci->msi = false;
#endif

	pci->msi = nvkm_boolopt(device->cfgopt, "NvMSI", pci->msi);
	if (pci->msi && func->msi_rearm) {
		pci->msi = pci_enable_msi(pci->pdev) == 0;
		if (pci->msi)
			nvkm_debug(&pci->subdev, "MSI enabled\n");
	} else {
		pci->msi = false;
	}

	return 0;
}
