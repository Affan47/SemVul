lpfc_prot_group_type(struct lpfc_hba *phba, struct scsi_cmnd *sc)
{
	int ret = LPFC_PG_TYPE_INVALID;
	unsigned char op = scsi_get_prot_op(sc);

	switch (op) {
	case SCSI_PROT_READ_STRIP:
	case SCSI_PROT_WRITE_INSERT:
		ret = LPFC_PG_TYPE_NO_DIF;
		break;
	case SCSI_PROT_READ_INSERT:
	case SCSI_PROT_WRITE_STRIP:
	case SCSI_PROT_READ_PASS:
	case SCSI_PROT_WRITE_PASS:
		ret = LPFC_PG_TYPE_DIF_BUF;
		break;
	default:
		if (phba)
			lpfc_printf_log(phba, KERN_ERR, LOG_FCP,
					"9021 Unsupported protection op:%d\n",
					op);
		break;
	}
	return ret;
}
