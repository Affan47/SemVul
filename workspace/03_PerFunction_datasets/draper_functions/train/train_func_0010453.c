parse_timecode_format(std::string tc, Timecode::Time &TC) {
	char negative[2];
	char ignored[2];
	TC.subframes = 0;
	if (sscanf (tc.c_str(), "%[- ]%" PRId32 ":%" PRId32 ":%" PRId32 "%[:;]%" PRId32,
				negative, &TC.hours, &TC.minutes, &TC.seconds, ignored, &TC.frames) != 6) {
		TC.hours = TC.minutes = TC.seconds = TC.frames = 0;
		TC.negative = false;
		return false;
	}
	if (negative[0]=='-') {
		TC.negative = true;
	} else {
		TC.negative = false;
	}
	return true;
}
