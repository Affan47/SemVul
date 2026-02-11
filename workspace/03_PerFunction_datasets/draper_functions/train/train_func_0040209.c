qla82xx_validate_template_chksum(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint64_t chksum = 0;
	uint32_t *d_ptr = (uint32_t *)ha->md_tmplt_hdr;
	int count = ha->md_template_size/sizeof(uint32_t);

	while (count-- > 0)
		chksum += *d_ptr++;
	while (chksum >> 32)
		chksum = (chksum & 0xFFFFFFFF) + (chksum >> 32);
	return ~chksum;
}
