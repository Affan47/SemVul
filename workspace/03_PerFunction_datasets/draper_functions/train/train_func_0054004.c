qla4_8xxx_clear_drv_active(struct scsi_qla_host *ha)
{
	uint32_t drv_active;

	drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);


	if (is_qla8032(ha) || is_qla8042(ha))
		drv_active &= ~(1 << (ha->func_num));
	else
		drv_active &= ~(1 << (ha->func_num * 4));

	ql4_printk(KERN_INFO, ha, "%s(%ld): drv_active: 0x%08x\n",
		   __func__, ha->host_no, drv_active);
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DRV_ACTIVE, drv_active);
}
