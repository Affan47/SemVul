acpi_thermal_rel_ioctl(struct file *f, unsigned int cmd,
				   unsigned long __arg)
{
	int ret = 0;
	unsigned long length = 0;
	int count = 0;
	char __user *arg = (void __user *)__arg;
	struct trt *trts = NULL;
	struct art *arts = NULL;

	switch (cmd) {
	case ACPI_THERMAL_GET_TRT_COUNT:
		ret = acpi_parse_trt(acpi_thermal_rel_handle, &count,
				&trts, false);
		kfree(trts);
		if (!ret)
			return put_user(count, (unsigned long __user *)__arg);
		return ret;
	case ACPI_THERMAL_GET_TRT_LEN:
		ret = acpi_parse_trt(acpi_thermal_rel_handle, &count,
				&trts, false);
		kfree(trts);
		length = count * sizeof(union trt_object);
		if (!ret)
			return put_user(length, (unsigned long __user *)__arg);
		return ret;
	case ACPI_THERMAL_GET_TRT:
		return fill_trt(arg);
	case ACPI_THERMAL_GET_ART_COUNT:
		ret = acpi_parse_art(acpi_thermal_rel_handle, &count,
				&arts, false);
		kfree(arts);
		if (!ret)
			return put_user(count, (unsigned long __user *)__arg);
		return ret;
	case ACPI_THERMAL_GET_ART_LEN:
		ret = acpi_parse_art(acpi_thermal_rel_handle, &count,
				&arts, false);
		kfree(arts);
		length = count * sizeof(union art_object);
		if (!ret)
			return put_user(length, (unsigned long __user *)__arg);
		return ret;

	case ACPI_THERMAL_GET_ART:
		return fill_art(arg);

	default:
		return -ENOTTY;
	}
}
