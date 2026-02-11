qla4_82xx_need_reset_handler(struct scsi_qla_host *ha)
{
	uint32_t dev_state, drv_state, drv_active;
	uint32_t active_mask = 0xFFFFFFFF;
	unsigned long reset_timeout;

	ql4_printk(KERN_INFO, ha,
		"Performing ISP error recovery\n");

	if (test_and_clear_bit(AF_ONLINE, &ha->flags)) {
		qla4_82xx_idc_unlock(ha);
		ha->isp_ops->disable_intrs(ha);
		qla4_82xx_idc_lock(ha);
	}

	if (!test_bit(AF_8XXX_RST_OWNER, &ha->flags)) {
		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "%s(%ld): reset acknowledged\n",
				  __func__, ha->host_no));
		qla4_8xxx_set_rst_ready(ha);
	} else {
		active_mask = (~(1 << (ha->func_num * 4)));
	}


	reset_timeout = jiffies + (ha->nx_reset_timeout * HZ);

	drv_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_active = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);

	ql4_printk(KERN_INFO, ha,
		"%s(%ld): drv_state = 0x%x, drv_active = 0x%x\n",
		__func__, ha->host_no, drv_state, drv_active);

	while (drv_state != (drv_active & active_mask)) {
		if (time_after_eq(jiffies, reset_timeout)) {
			ql4_printk(KERN_INFO, ha,
				   "%s: RESET TIMEOUT! drv_state: 0x%08x, drv_active: 0x%08x\n",
				   DRIVER_NAME, drv_state, drv_active);
			break;
		}


		if (test_bit(AF_8XXX_RST_OWNER, &ha->flags)) {
			ql4_printk(KERN_INFO, ha,
				   "%s(%ld): drv_state = 0x%x, drv_active = 0x%x\n",
				   __func__, ha->host_no, drv_state,
				   drv_active);
		}
		qla4_82xx_idc_unlock(ha);
		msleep(1000);
		qla4_82xx_idc_lock(ha);

		drv_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		drv_active = qla4_82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	}


	clear_bit(AF_8XXX_RST_OWNER, &ha->flags);

	dev_state = qla4_82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	ql4_printk(KERN_INFO, ha, "Device state is 0x%x = %s\n", dev_state,
		   dev_state < MAX_STATES ? qdev_state[dev_state] : "Unknown");


	if (dev_state != QLA8XXX_DEV_INITIALIZING) {
		ql4_printk(KERN_INFO, ha, "HW State: COLD/RE-INIT\n");
		qla4_82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_COLD);
		qla4_8xxx_set_rst_ready(ha);
	}
}
