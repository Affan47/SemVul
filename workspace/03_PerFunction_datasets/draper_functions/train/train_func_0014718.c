load_temp_cutoffs()
{
	int i, val = 0, device = 0;
	char *nextptr;

	if (temp_cutoff_str) {
		for (device = 0, nextptr = strtok(temp_cutoff_str, ","); nextptr; ++device, nextptr = strtok(NULL, ",")) {
			if (device >= total_devices)
				quit(1, "Too many values passed to set temp cutoff");
			val = atoi(nextptr);
			if (val < 0 || val > 200)
				quit(1, "Invalid value passed to set temp cutoff");

			rd_lock(&devices_lock);
			devices[device]->cutofftemp = val;
			rd_unlock(&devices_lock);
		}
	} else {
		rd_lock(&devices_lock);
		for (i = device; i < total_devices; ++i) {
			if (!devices[i]->cutofftemp)
				devices[i]->cutofftemp = opt_cutofftemp;
		}
		rd_unlock(&devices_lock);

		return;
	}
	if (device <= 1) {
		rd_lock(&devices_lock);
		for (i = device; i < total_devices; ++i)
			devices[i]->cutofftemp = val;
		rd_unlock(&devices_lock);
	}
}
