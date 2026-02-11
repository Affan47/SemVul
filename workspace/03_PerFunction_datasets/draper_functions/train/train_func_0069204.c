gf_oci_event_get_duration(OCIEvent *event, u8 *Hours, u8 *Minutes, u8 *Seconds, u8 *HundredSeconds)
{
	if (!event || !Hours || !Minutes || !Seconds || !HundredSeconds)
		return GF_BAD_PARAM;

	*Hours = event->duration[0];
	*Minutes = event->duration[1];
	*Seconds = event->duration[2];
	*HundredSeconds = event->duration[3];
	return GF_OK;
}
