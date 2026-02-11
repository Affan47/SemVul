netxen_nic_get_board_info(struct netxen_adapter *adapter)
{
	int offset, board_type, magic;
	struct pci_dev *pdev = adapter->pdev;

	offset = NX_FW_MAGIC_OFFSET;
	if (netxen_rom_fast_read(adapter, offset, &magic))
		return -EIO;

	if (magic != NETXEN_BDINFO_MAGIC) {
		dev_err(&pdev->dev, "invalid board config, magic=%08x\n",
			magic);
		return -EIO;
	}

	offset = NX_BRDTYPE_OFFSET;
	if (netxen_rom_fast_read(adapter, offset, &board_type))
		return -EIO;

	if (board_type == NETXEN_BRDTYPE_P3_4_GB_MM) {
		u32 gpio = NXRD32(adapter, NETXEN_ROMUSB_GLB_PAD_GPIO_I);
		if ((gpio & 0x8000) == 0)
			board_type = NETXEN_BRDTYPE_P3_10G_TP;
	}

	adapter->ahw.board_type = board_type;

	switch (board_type) {
	case NETXEN_BRDTYPE_P2_SB35_4G:
		adapter->ahw.port_type = NETXEN_NIC_GBE;
		break;
	case NETXEN_BRDTYPE_P2_SB31_10G:
	case NETXEN_BRDTYPE_P2_SB31_10G_IMEZ:
	case NETXEN_BRDTYPE_P2_SB31_10G_HMEZ:
	case NETXEN_BRDTYPE_P2_SB31_10G_CX4:
	case NETXEN_BRDTYPE_P3_HMEZ:
	case NETXEN_BRDTYPE_P3_XG_LOM:
	case NETXEN_BRDTYPE_P3_10G_CX4:
	case NETXEN_BRDTYPE_P3_10G_CX4_LP:
	case NETXEN_BRDTYPE_P3_IMEZ:
	case NETXEN_BRDTYPE_P3_10G_SFP_PLUS:
	case NETXEN_BRDTYPE_P3_10G_SFP_CT:
	case NETXEN_BRDTYPE_P3_10G_SFP_QT:
	case NETXEN_BRDTYPE_P3_10G_XFP:
	case NETXEN_BRDTYPE_P3_10000_BASE_T:
		adapter->ahw.port_type = NETXEN_NIC_XGBE;
		break;
	case NETXEN_BRDTYPE_P1_BD:
	case NETXEN_BRDTYPE_P1_SB:
	case NETXEN_BRDTYPE_P1_SMAX:
	case NETXEN_BRDTYPE_P1_SOCK:
	case NETXEN_BRDTYPE_P3_REF_QG:
	case NETXEN_BRDTYPE_P3_4_GB:
	case NETXEN_BRDTYPE_P3_4_GB_MM:
		adapter->ahw.port_type = NETXEN_NIC_GBE;
		break;
	case NETXEN_BRDTYPE_P3_10G_TP:
		adapter->ahw.port_type = (adapter->portnum < 2) ?
			NETXEN_NIC_XGBE : NETXEN_NIC_GBE;
		break;
	default:
		dev_err(&pdev->dev, "unknown board type %x\n", board_type);
		adapter->ahw.port_type = NETXEN_NIC_XGBE;
		break;
	}

	return 0;
}
