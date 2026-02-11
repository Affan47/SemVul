isns_event_string(unsigned int bits)
{
	static const char *names[16] = {
	[ISNS_SCN_DD_MEMBER_ADDED]	= "member added",
	[ISNS_SCN_DD_MEMBER_REMOVED]	= "member removed",
	[ISNS_SCN_OBJECT_UPDATED]	= "updated",
	[ISNS_SCN_OBJECT_ADDED]		= "added",
	[ISNS_SCN_OBJECT_REMOVED]	= "removed",
	[ISNS_SCN_MANAGEMENT_REGISTRATION]= "mgmt registration",
	[ISNS_SCN_TARGET_AND_SELF_ONLY]	= "target+self",
	[ISNS_SCN_INITIATOR_AND_SELF_ONLY]= "initiator+self",
	};
	static char	buffer[128];
	unsigned int	pos = 0, i;


	for (i = 0; i < 16; ++i, bits >>= 1) {
		if (!(bits & 1))
			continue;

		if (names[i]) {
			snprintf(buffer + pos, sizeof(buffer) - pos,
				"%s%s", pos? ", " : "", names[i]);
		} else {
			snprintf(buffer + pos, sizeof(buffer) - pos,
				"%sevent %u", pos? ", " : "", i);
		}
		pos = strlen(buffer);
	}
	if (pos == 0)
		return "<no event>";

	return buffer;
}
