vfio_ext_cap_len(struct vfio_pci_device *vdev, u16 ecap, u16 epos)
{
	struct pci_dev *pdev = vdev->pdev;
	u8 byte;
	u32 dword;
	int ret;

	switch (ecap) {
	case PCI_EXT_CAP_ID_VNDR:
		ret = pci_read_config_dword(pdev, epos + PCI_VSEC_HDR, &dword);
		if (ret)
			return pcibios_err_to_errno(ret);

		return dword >> PCI_VSEC_HDR_LEN_SHIFT;
	case PCI_EXT_CAP_ID_VC:
	case PCI_EXT_CAP_ID_VC9:
	case PCI_EXT_CAP_ID_MFVC:
		return vfio_vc_cap_len(vdev, epos);
	case PCI_EXT_CAP_ID_ACS:
		ret = pci_read_config_byte(pdev, epos + PCI_ACS_CAP, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		if (byte & PCI_ACS_EC) {
			int bits;

			ret = pci_read_config_byte(pdev,
						   epos + PCI_ACS_EGRESS_BITS,
						   &byte);
			if (ret)
				return pcibios_err_to_errno(ret);

			bits = byte ? round_up(byte, 32) : 256;
			return 8 + (bits / 8);
		}
		return 8;

	case PCI_EXT_CAP_ID_REBAR:
		ret = pci_read_config_byte(pdev, epos + PCI_REBAR_CTRL, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		byte &= PCI_REBAR_CTRL_NBAR_MASK;
		byte >>= PCI_REBAR_CTRL_NBAR_SHIFT;

		return 4 + (byte * 8);
	case PCI_EXT_CAP_ID_DPA:
		ret = pci_read_config_byte(pdev, epos + PCI_DPA_CAP, &byte);
		if (ret)
			return pcibios_err_to_errno(ret);

		byte &= PCI_DPA_CAP_SUBSTATE_MASK;
		return PCI_DPA_BASE_SIZEOF + byte + 1;
	case PCI_EXT_CAP_ID_TPH:
		ret = pci_read_config_dword(pdev, epos + PCI_TPH_CAP, &dword);
		if (ret)
			return pcibios_err_to_errno(ret);

		if ((dword & PCI_TPH_CAP_LOC_MASK) == PCI_TPH_LOC_CAP) {
			int sts;

			sts = dword & PCI_TPH_CAP_ST_MASK;
			sts >>= PCI_TPH_CAP_ST_SHIFT;
			return PCI_TPH_BASE_SIZEOF + (sts * 2) + 2;
		}
		return PCI_TPH_BASE_SIZEOF;
	default:
		pr_warn("%s: %s unknown length for pci ecap 0x%x@0x%x\n",
			dev_name(&pdev->dev), __func__, ecap, epos);
	}

	return 0;
}
