increment_subframes (Time& timecode, uint32_t subframes_per_frame)
{
	Wrap wrap = NONE;

	if (timecode.negative) {
		timecode.negative = false;
		wrap = decrement_subframes (timecode, subframes_per_frame);
		if (!Timecode_IS_ZERO (timecode)) {
			timecode.negative = true;
		}
		return wrap;
	}

	timecode.subframes++;
	if (timecode.subframes >= subframes_per_frame) {
		timecode.subframes = 0;
		increment (timecode, subframes_per_frame);
		return FRAMES;
	}
	return NONE;
}
