sff8079_show_connector(const __u8 *id)
{
	printf("\t%-41s : 0x%02x", "Connector", id[2]);
	switch (id[2]) {
	case 0x00:
		printf(" (unknown or unspecified)\n");
		break;
	case 0x01:
		printf(" (SC)\n");
		break;
	case 0x02:
		printf(" (Fibre Channel Style 1 copper)\n");
		break;
	case 0x03:
		printf(" (Fibre Channel Style 2 copper)\n");
		break;
	case 0x04:
		printf(" (BNC/TNC)\n");
		break;
	case 0x05:
		printf(" (Fibre Channel coaxial headers)\n");
		break;
	case 0x06:
		printf(" (FibreJack)\n");
		break;
	case 0x07:
		printf(" (LC)\n");
		break;
	case 0x08:
		printf(" (MT-RJ)\n");
		break;
	case 0x09:
		printf(" (MU)\n");
		break;
	case 0x0a:
		printf(" (SG)\n");
		break;
	case 0x0b:
		printf(" (Optical pigtail)\n");
		break;
	case 0x0c:
		printf(" (MPO Parallel Optic)\n");
		break;
	case 0x20:
		printf(" (HSSDC II)\n");
		break;
	case 0x21:
		printf(" (Copper pigtail)\n");
		break;
	case 0x22:
		printf(" (RJ45)\n");
		break;
	default:
		printf(" (reserved or unknown)\n");
		break;
	}
}
