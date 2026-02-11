qla4_83xx_template_end(struct scsi_qla_host *ha,
				   struct qla4_83xx_reset_entry_hdr *p_hdr)
{
	ha->reset_tmplt.template_end = 1;

	if (ha->reset_tmplt.seq_error == 0) {
		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "%s: Reset sequence completed SUCCESSFULLY.\n",
				  __func__));
	} else {
		ql4_printk(KERN_ERR, ha, "%s: Reset sequence completed with some timeout errors.\n",
			   __func__);
	}
}
