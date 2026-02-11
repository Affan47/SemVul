apds990x_rate_avail(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int i;
	int pos = 0;
	for (i = 0; i < ARRAY_SIZE(arates_hz); i++)
		pos += sprintf(buf + pos, "%d ", arates_hz[i]);
	sprintf(buf + pos - 1, "\n");
	return pos;
}
