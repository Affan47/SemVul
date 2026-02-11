vfio_ecap_init(struct vfio_pci_device *vdev)
{
	struct pci_dev *pdev = vdev->pdev;
	u8 *map = vdev->pci_config_map;
	u16 epos;
	__le32 *prev = NULL;
	int loops, ret, ecaps = 0;

	if (!vdev->extended_caps)
		return 0;

	epos = PCI_CFG_SPACE_SIZE;

	loops = (pdev->cfg_size - PCI_CFG_SPACE_SIZE) / PCI_CAP_SIZEOF;

	while (loops-- && epos >= PCI_CFG_SPACE_SIZE) {
		u32 header;
		u16 ecap;
		int i, len = 0;
		bool hidden = false;

		ret = pci_read_config_dword(pdev, epos, &header);
		if (ret)
			return ret;

		ecap = PCI_EXT_CAP_ID(header);

		if (ecap <= PCI_EXT_CAP_ID_MAX) {
			len = pci_ext_cap_length[ecap];
			if (len == 0xFF) {
				len = vfio_ext_cap_len(vdev, ecap, epos);
				if (len < 0)
					return ret;
			}
		}

		if (!len) {
			pr_info("%s: %s hiding ecap 0x%x@0x%x\n",
				__func__, dev_name(&pdev->dev), ecap, epos);


			if (prev) {
				u32 val = epos = PCI_EXT_CAP_NEXT(header);
				*prev &= cpu_to_le32(~(0xffcU << 20));
				*prev |= cpu_to_le32(val << 20);
				continue;
			}


			len = PCI_CAP_SIZEOF;
			hidden = true;
		}

		for (i = 0; i < len; i++) {
			if (likely(map[epos + i] == PCI_CAP_ID_INVALID))
				continue;

			pr_warn("%s: %s pci config conflict @0x%x, was ecap 0x%x now ecap 0x%x\n",
				__func__, dev_name(&pdev->dev),
				epos + i, map[epos + i], ecap);
		}


		BUILD_BUG_ON(PCI_EXT_CAP_ID_MAX >= PCI_CAP_ID_INVALID);

		memset(map + epos, ecap, len);
		ret = vfio_fill_vconfig_bytes(vdev, epos, len);
		if (ret)
			return ret;


		if (hidden)
			*(__le32 *)&vdev->vconfig[epos] &=
				cpu_to_le32((0xffcU << 20));
		else
			ecaps++;

		prev = (__le32 *)&vdev->vconfig[epos];
		epos = PCI_EXT_CAP_NEXT(header);
	}

	if (!ecaps)
		*(u32 *)&vdev->vconfig[PCI_CFG_SPACE_SIZE] = 0;

	return 0;
}
