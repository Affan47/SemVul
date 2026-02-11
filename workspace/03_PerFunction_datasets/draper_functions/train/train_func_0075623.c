qla4_8xxx_minidump_process_rdocm(struct scsi_qla_host *ha,
				struct qla8xxx_minidump_entry_hdr *entry_hdr,
				uint32_t **d_ptr)
{
	uint32_t r_addr, r_stride, loop_cnt, i, r_value;
	struct qla8xxx_minidump_entry_rdocm *ocm_hdr;
	uint32_t *data_ptr = *d_ptr;

	DEBUG2(ql4_printk(KERN_INFO, ha, "Entering fn: %s\n", __func__));
	ocm_hdr = (struct qla8xxx_minidump_entry_rdocm *)entry_hdr;
	r_addr = ocm_hdr->read_addr;
	r_stride = ocm_hdr->read_addr_stride;
	loop_cnt = ocm_hdr->op_count;

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "[%s]: r_addr: 0x%x, r_stride: 0x%x, loop_cnt: 0x%x\n",
			  __func__, r_addr, r_stride, loop_cnt));

	for (i = 0; i < loop_cnt; i++) {
		r_value = readl((void __iomem *)(r_addr + ha->nx_pcibase));
		*data_ptr++ = cpu_to_le32(r_value);
		r_addr += r_stride;
	}
	DEBUG2(ql4_printk(KERN_INFO, ha, "Leaving fn: %s datacount: 0x%lx\n",
		__func__, (long unsigned int) (loop_cnt * sizeof(uint32_t))));
	*d_ptr = data_ptr;
}
