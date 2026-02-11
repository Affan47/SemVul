ql_log(uint32_t level, scsi_qla_host_t *vha, int32_t id, const char *fmt, ...)
{
	va_list va;
	struct va_format vaf;
	char pbuf[128];

	if (level > ql_errlev)
		return;

	if (vha != NULL) {
		const struct pci_dev *pdev = vha->hw->pdev;

		snprintf(pbuf, sizeof(pbuf), "%s [%s]-%04x:%ld: ",
			QL_MSGHDR, dev_name(&(pdev->dev)), id, vha->host_no);
	} else {
		snprintf(pbuf, sizeof(pbuf), "%s [%s]-%04x: : ",
			QL_MSGHDR, "0000:00:00.0", id);
	}
	pbuf[sizeof(pbuf) - 1] = 0;

	va_start(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	switch (level) {
	case ql_log_fatal:
		pr_crit("%s%pV", pbuf, &vaf);
		break;
	case ql_log_warn:
		pr_err("%s%pV", pbuf, &vaf);
		break;
	case ql_log_info:
		pr_warn("%s%pV", pbuf, &vaf);
		break;
	default:
		pr_info("%s%pV", pbuf, &vaf);
		break;
	}

	va_end(va);
}
