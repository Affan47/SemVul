ips_scmd_buf_write(struct scsi_cmnd *scmd, void *data, unsigned int count)
{
	unsigned long flags;

	local_irq_save(flags);
	scsi_sg_copy_from_buffer(scmd, data, count);
	local_irq_restore(flags);
}
