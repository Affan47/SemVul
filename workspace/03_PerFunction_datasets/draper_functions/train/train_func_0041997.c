smiapp_write(struct smiapp_sensor *sensor, u32 reg, u32 val)
{
	int rval;

	rval = smiapp_call_quirk(sensor, reg_access, true, &reg, &val);
	if (rval == -ENOIOCTLCMD)
		return 0;
	if (rval < 0)
		return rval;

	return smiapp_write_no_quirk(sensor, reg, val);
}
