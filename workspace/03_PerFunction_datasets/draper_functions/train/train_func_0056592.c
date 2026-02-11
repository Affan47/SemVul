qat_uclo_check_format(struct icp_qat_uof_filehdr *hdr)
{
	int maj = hdr->maj_ver & 0xff;
	int min = hdr->min_ver & 0xff;

	if (hdr->file_id != ICP_QAT_UOF_FID) {
		pr_err("QAT: Invalid header 0x%x\n", hdr->file_id);
		return -EINVAL;
	}
	if (min != ICP_QAT_UOF_MINVER || maj != ICP_QAT_UOF_MAJVER) {
		pr_err("QAT: bad UOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		return -EINVAL;
	}
	return 0;
}
