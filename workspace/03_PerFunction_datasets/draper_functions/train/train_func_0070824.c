bochs_hw_init(struct drm_device *dev, uint32_t flags)
{
	struct bochs_device *bochs = dev->dev_private;
	struct pci_dev *pdev = dev->pdev;
	unsigned long addr, size, mem, ioaddr, iosize, qext_size;
	u16 id;

	if (pdev->resource[2].flags & IORESOURCE_MEM) {

		if (pci_request_region(pdev, 2, "bochs-drm") != 0) {
			DRM_ERROR("Cannot request mmio region\n");
			return -EBUSY;
		}
		ioaddr = pci_resource_start(pdev, 2);
		iosize = pci_resource_len(pdev, 2);
		bochs->mmio = ioremap(ioaddr, iosize);
		if (bochs->mmio == NULL) {
			DRM_ERROR("Cannot map mmio region\n");
			return -ENOMEM;
		}
	} else {
		ioaddr = VBE_DISPI_IOPORT_INDEX;
		iosize = 2;
		if (!request_region(ioaddr, iosize, "bochs-drm")) {
			DRM_ERROR("Cannot request ioports\n");
			return -EBUSY;
		}
		bochs->ioports = 1;
	}

	id = bochs_dispi_read(bochs, VBE_DISPI_INDEX_ID);
	mem = bochs_dispi_read(bochs, VBE_DISPI_INDEX_VIDEO_MEMORY_64K)
		* 64 * 1024;
	if ((id & 0xfff0) != VBE_DISPI_ID0) {
		DRM_ERROR("ID mismatch\n");
		return -ENODEV;
	}

	if ((pdev->resource[0].flags & IORESOURCE_MEM) == 0)
		return -ENODEV;
	addr = pci_resource_start(pdev, 0);
	size = pci_resource_len(pdev, 0);
	if (addr == 0)
		return -ENODEV;
	if (size != mem) {
		DRM_ERROR("Size mismatch: pci=%ld, bochs=%ld\n",
			size, mem);
		size = min(size, mem);
	}

	if (pci_request_region(pdev, 0, "bochs-drm") != 0) {
		DRM_ERROR("Cannot request framebuffer\n");
		return -EBUSY;
	}

	bochs->fb_map = ioremap(addr, size);
	if (bochs->fb_map == NULL) {
		DRM_ERROR("Cannot map framebuffer\n");
		return -ENOMEM;
	}
	bochs->fb_base = addr;
	bochs->fb_size = size;

	DRM_INFO("Found bochs VGA, ID 0x%x.\n", id);
	DRM_INFO("Framebuffer size %ld kB @ 0x%lx, %s @ 0x%lx.\n",
		 size / 1024, addr,
		 bochs->ioports ? "ioports" : "mmio",
		 ioaddr);

	if (bochs->mmio && pdev->revision >= 2) {
		qext_size = readl(bochs->mmio + 0x600);
		if (qext_size < 4 || qext_size > iosize)
			goto noext;
		DRM_DEBUG("Found qemu ext regs, size %ld\n", qext_size);
		if (qext_size >= 8) {
#ifdef __BIG_ENDIAN
			writel(0xbebebebe, bochs->mmio + 0x604);
#else
			writel(0x1e1e1e1e, bochs->mmio + 0x604);
#endif
			DRM_DEBUG("  qext endian: 0x%x\n",
				  readl(bochs->mmio + 0x604));
		}
	}

noext:
	return 0;
}
