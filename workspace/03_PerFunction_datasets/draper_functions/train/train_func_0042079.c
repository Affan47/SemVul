hour2bcd(bool hr12, int hour)
{
	if (hr12) {
		hour++;
		if (hour <= 12)
			return DS1305_HR_12 | bin2bcd(hour);
		hour -= 12;
		return DS1305_HR_12 | DS1305_HR_PM | bin2bcd(hour);
	}
	return bin2bcd(hour);
}
