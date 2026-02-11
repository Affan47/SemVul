via_pci_setup_mmio(struct viafb_dev *vdev)
{
	int ret;


	vdev->engine_start = pci_resource_start(vdev->pdev, 1);
	vdev->engine_len = pci_resource_len(vdev->pdev, 1);
	vdev->engine_mmio = ioremap_nocache(vdev->engine_start,
			vdev->engine_len);
	if (vdev->engine_mmio == NULL)
		dev_err(&vdev->pdev->dev,
				"Unable to map engine MMIO; operation will be "
				"slow and crippled.\n");


	if (vdev->chip_type == UNICHROME_VX900)
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 2);
	else
		vdev->fbmem_start = pci_resource_start(vdev->pdev, 0);
	ret = vdev->fbmem_len = viafb_get_fb_size_from_pci(vdev->chip_type);
	if (ret < 0)
		goto out_unmap;


	for (; vdev->fbmem_len >= 8 << 20; vdev->fbmem_len /= 2) {
		vdev->fbmem = ioremap_wc(vdev->fbmem_start, vdev->fbmem_len);
		if (vdev->fbmem)
			break;
	}

	if (vdev->fbmem == NULL) {
		ret = -ENOMEM;
		goto out_unmap;
	}
	return 0;
out_unmap:
	iounmap(vdev->engine_mmio);
	return ret;
}
