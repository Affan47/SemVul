ql_log_pci(uint32_t level, struct pci_dev *pdev, int32_t id,
	   const char *fmt, ...)
{
	va_list va;
	struct va_format vaf;
	char pbuf[128];

	if (pdev == NULL)
		return;
	if (level > ql_errlev)
		return;


	snprintf(pbuf, sizeof(pbuf), "%s [%s]-%04x: : ",
		 QL_MSGHDR, dev_name(&(pdev->dev)), id);
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
