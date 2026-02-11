efi_runtime_get_time(unsigned long arg)
{
	struct efi_gettime __user *gettime_user;
	struct efi_gettime  gettime;
	efi_status_t status;
	efi_time_cap_t cap;
	efi_time_t efi_time;

	gettime_user = (struct efi_gettime __user *)arg;
	if (copy_from_user(&gettime, gettime_user, sizeof(gettime)))
		return -EFAULT;

	status = efi.get_time(gettime.time ? &efi_time : NULL,
			      gettime.capabilities ? &cap : NULL);

	if (put_user(status, gettime.status))
		return -EFAULT;

	if (status != EFI_SUCCESS)
		return -EINVAL;

	if (gettime.capabilities) {
		efi_time_cap_t __user *cap_local;

		cap_local = (efi_time_cap_t *)gettime.capabilities;
		if (put_user(cap.resolution, &(cap_local->resolution)) ||
			put_user(cap.accuracy, &(cap_local->accuracy)) ||
			put_user(cap.sets_to_zero, &(cap_local->sets_to_zero)))
			return -EFAULT;
	}
	if (gettime.time) {
		if (copy_to_user(gettime.time, &efi_time, sizeof(efi_time_t)))
			return -EFAULT;
	}

	return 0;
}
