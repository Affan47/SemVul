megasas_reset_bus_host(struct scsi_cmnd *scmd)
{
	int ret;
	struct megasas_instance *instance;

	instance = (struct megasas_instance *)scmd->device->host->hostdata;


	if (instance->ctrl_context)
		ret = megasas_reset_fusion(scmd->device->host, 1);
	else
		ret = megasas_generic_reset(scmd);

	return ret;
}
