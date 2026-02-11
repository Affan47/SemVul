gf_oci_event_set_duration(OCIEvent *event, u8 Hours, u8 Minutes, u8 Seconds, u8 HundredSeconds)
{
	if (!event || (Hours >= 100) || (Minutes >= 100) || (Seconds >= 100) || (HundredSeconds >= 100) )
		return GF_BAD_PARAM;

	event->duration[0] = Hours;
	event->duration[1] = Minutes;
	event->duration[2] = Seconds;
	event->duration[3] = HundredSeconds;
	return GF_OK;
}
