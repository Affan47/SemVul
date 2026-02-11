fan_write_cmd_level(const char *cmd, int *rc)
{
	int level;

	if (strlencmp(cmd, "level auto") == 0)
		level = TP_EC_FAN_AUTO;
	else if ((strlencmp(cmd, "level disengaged") == 0) |
			(strlencmp(cmd, "level full-speed") == 0))
		level = TP_EC_FAN_FULLSPEED;
	else if (sscanf(cmd, "level %d", &level) != 1)
		return 0;

	*rc = fan_set_level_safe(level);
	if (*rc == -ENXIO)
		pr_err("level command accepted for unsupported access mode %d\n",
		       fan_control_access_mode);
	else if (!*rc)
		tpacpi_disclose_usertask("procfs fan",
			"set level to %d\n", level);

	return 1;
}
