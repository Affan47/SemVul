_scsih_check_access_status(struct MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u16 handle, u8 access_status)
{
	u8 rc = 1;
	char *desc = NULL;

	switch (access_status) {
	case MPI2_SAS_DEVICE0_ASTATUS_NO_ERRORS:
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_NEEDS_INITIALIZATION:
		rc = 0;
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_CAPABILITY_FAILED:
		desc = "sata capability failed";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_AFFILIATION_CONFLICT:
		desc = "sata affiliation conflict";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_ROUTE_NOT_ADDRESSABLE:
		desc = "route not addressable";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SMP_ERROR_NOT_ADDRESSABLE:
		desc = "smp error not addressable";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_DEVICE_BLOCKED:
		desc = "device blocked";
		break;
	case MPI2_SAS_DEVICE0_ASTATUS_SATA_INIT_FAILED:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_UNKNOWN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_AFFILIATION_CONFLICT:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_DIAG:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_IDENTIFICATION:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_CHECK_POWER:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_PIO_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_MDMA_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_UDMA_SN:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_ZONING_VIOLATION:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_NOT_ADDRESSABLE:
	case MPI2_SAS_DEVICE0_ASTATUS_SIF_MAX:
		desc = "sata initialization failed";
		break;
	default:
		desc = "unknown";
		break;
	}

	if (!rc)
		return 0;

	pr_err(MPT3SAS_FMT
		"discovery errors(%s): sas_address(0x%016llx), handle(0x%04x)\n",
		ioc->name, desc, (unsigned long long)sas_address, handle);
	return rc;
}
