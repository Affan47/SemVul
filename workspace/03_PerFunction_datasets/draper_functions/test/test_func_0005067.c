qla82xx_read_flash_data(scsi_qla_host_t *vha, uint32_t *dwptr, uint32_t faddr,
	uint32_t length)
{
	uint32_t i;
	uint32_t val;
	struct qla_hw_data *ha = vha->hw;


	for (i = 0; i < length/4; i++, faddr += 4) {
		if (qla82xx_rom_fast_read(ha, faddr, &val)) {
			ql_log(ql_log_warn, vha, 0x0106,
			    "Do ROM fast read failed.\n");
			goto done_read;
		}
		dwptr[i] = cpu_to_le32(val);
	}
done_read:
	return dwptr;
}
