fan_write_cmd_disable(const char *cmd, int *rc)
{
	if (strlencmp(cmd, "disable") != 0)
		return 0;

	*rc = fan_set_disable();
	if (*rc == -ENXIO)
		pr_err("disable command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	else if (!*rc)
		tpacpi_disclose_usertask("procfs fan", "disable\n");

	return 1;
}
