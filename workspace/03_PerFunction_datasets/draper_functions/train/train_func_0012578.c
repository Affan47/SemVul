format_value (char *buff, double value, char *unit)
{
	char *mag;


	if (strstr(unit, "b"))
		value *= 8;


	mag = convert_double(&value, (strstr(unit, "B")) ? 1024 : 1000, 1.0f);


	if (mag[0] == 0)
		sprintf(buff, "%8ld %s", (long) value, unit);
	else
		sprintf(buff, "%7.3f %s%s", value, mag, unit);

}
