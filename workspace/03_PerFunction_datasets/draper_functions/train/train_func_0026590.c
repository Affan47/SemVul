ds1286_proc(struct device *dev, struct seq_file *seq)
{
	struct ds1286_priv *priv = dev_get_drvdata(dev);
	unsigned char month, cmd, amode;
	const char *s;

	month = ds1286_rtc_read(priv, RTC_MONTH);
	seq_printf(seq,
		   "oscillator\t: %s\n"
		   "square_wave\t: %s\n",
		   (month & RTC_EOSC) ? "disabled" : "enabled",
		   (month & RTC_ESQW) ? "disabled" : "enabled");

	amode = ((ds1286_rtc_read(priv, RTC_MINUTES_ALARM) & 0x80) >> 5) |
		((ds1286_rtc_read(priv, RTC_HOURS_ALARM) & 0x80) >> 6) |
		((ds1286_rtc_read(priv, RTC_DAY_ALARM) & 0x80) >> 7);
	switch (amode) {
	case 7:
		s = "each minute";
		break;
	case 3:
		s = "minutes match";
		break;
	case 1:
		s = "hours and minutes match";
		break;
	case 0:
		s = "days, hours and minutes match";
		break;
	default:
		s = "invalid";
		break;
	}
	seq_printf(seq, "alarm_mode\t: %s\n", s);

	cmd = ds1286_rtc_read(priv, RTC_CMD);
	seq_printf(seq,
		   "alarm_enable\t: %s\n"
		   "wdog_alarm\t: %s\n"
		   "alarm_mask\t: %s\n"
		   "wdog_alarm_mask\t: %s\n"
		   "interrupt_mode\t: %s\n"
		   "INTB_mode\t: %s_active\n"
		   "interrupt_pins\t: %s\n",
		   (cmd & RTC_TDF) ? "yes" : "no",
		   (cmd & RTC_WAF) ? "yes" : "no",
		   (cmd & RTC_TDM) ? "disabled" : "enabled",
		   (cmd & RTC_WAM) ? "disabled" : "enabled",
		   (cmd & RTC_PU_LVL) ? "pulse" : "level",
		   (cmd & RTC_IBH_LO) ? "low" : "high",
		   (cmd & RTC_IPSW) ? "unswapped" : "swapped");
	return 0;
}
