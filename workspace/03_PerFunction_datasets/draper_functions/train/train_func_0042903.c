qla4_8xxx_ms_mem_write_128b(struct scsi_qla_host *ha, uint64_t addr,
				uint32_t *data, uint32_t count)
{
	int i, j;
	uint32_t agt_ctrl;
	unsigned long flags;
	int ret_val = QLA_SUCCESS;


	if (addr & 0xF) {
		ret_val = QLA_ERROR;
		goto exit_ms_mem_write;
	}

	write_lock_irqsave(&ha->hw_lock, flags);


	ret_val = ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_ADDR_HI, 0);
	if (ret_val == QLA_ERROR) {
		ql4_printk(KERN_ERR, ha, "%s: write to AGT_ADDR_HI failed\n",
			   __func__);
		goto exit_ms_mem_write_unlock;
	}

	for (i = 0; i < count; i++, addr += 16) {
		if (!((QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_QDR_NET,
					     QLA8XXX_ADDR_QDR_NET_MAX)) ||
		      (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
					     QLA8XXX_ADDR_DDR_NET_MAX)))) {
			ret_val = QLA_ERROR;
			goto exit_ms_mem_write_unlock;
		}

		ret_val = ha->isp_ops->wr_reg_indirect(ha,
						       MD_MIU_TEST_AGT_ADDR_LO,
						       addr);

		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_LO,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_HI,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_ULO,
						*data++);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
						MD_MIU_TEST_AGT_WRDATA_UHI,
						*data++);
		if (ret_val == QLA_ERROR) {
			ql4_printk(KERN_ERR, ha, "%s: write to AGT_WRDATA failed\n",
				   __func__);
			goto exit_ms_mem_write_unlock;
		}


		ret_val = ha->isp_ops->wr_reg_indirect(ha, MD_MIU_TEST_AGT_CTRL,
						       MIU_TA_CTL_WRITE_ENABLE);
		ret_val |= ha->isp_ops->wr_reg_indirect(ha,
							MD_MIU_TEST_AGT_CTRL,
							MIU_TA_CTL_WRITE_START);
		if (ret_val == QLA_ERROR) {
			ql4_printk(KERN_ERR, ha, "%s: write to AGT_CTRL failed\n",
				   __func__);
			goto exit_ms_mem_write_unlock;
		}

		for (j = 0; j < MAX_CTL_CHECK; j++) {
			ret_val = ha->isp_ops->rd_reg_indirect(ha,
							MD_MIU_TEST_AGT_CTRL,
							&agt_ctrl);
			if (ret_val == QLA_ERROR) {
				ql4_printk(KERN_ERR, ha, "%s: failed to read MD_MIU_TEST_AGT_CTRL\n",
					   __func__);
				goto exit_ms_mem_write_unlock;
			}
			if ((agt_ctrl & MIU_TA_CTL_BUSY) == 0)
				break;
		}


		if (j >= MAX_CTL_CHECK) {
			printk_ratelimited(KERN_ERR "%s: MS memory write failed!\n",
					   __func__);
			ret_val = QLA_ERROR;
			goto exit_ms_mem_write_unlock;
		}
	}

exit_ms_mem_write_unlock:
	write_unlock_irqrestore(&ha->hw_lock, flags);

exit_ms_mem_write:
	return ret_val;
}
