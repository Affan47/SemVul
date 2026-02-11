adjust_mostdevs(void)
{
	if (total_devices - zombie_devs > most_devices)
		most_devices = total_devices - zombie_devs;
}
