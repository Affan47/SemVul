memstick_power_on(struct memstick_host *host)
{
	int rc = host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_ON);

	if (!rc)
		rc = host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_SERIAL);

	return rc;
}
