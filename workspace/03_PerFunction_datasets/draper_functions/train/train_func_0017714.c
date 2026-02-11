esas2r_host_bus_reset(struct scsi_cmnd *cmd, bool host_reset)
{
	struct esas2r_adapter *a =
		(struct esas2r_adapter *)cmd->device->host->hostdata;

	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		return FAILED;

	if (host_reset)
		esas2r_reset_adapter(a);
	else
		esas2r_reset_bus(a);


	while (test_bit(AF_OS_RESET, &a->flags)) {
		msleep(10);

		if (test_bit(AF_DEGRADED_MODE, &a->flags))
			return FAILED;
	}

	if (test_bit(AF_DEGRADED_MODE, &a->flags))
		return FAILED;

	return SUCCESS;
}
