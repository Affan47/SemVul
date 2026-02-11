notice_interlace_seen (bool lace)
{
	bool changed = false;

	if (lace) {
		if (interlace_seen == 0) {
			changed = true;

		}
		interlace_seen = currprefs.gfx_vresolution ? 1 : -1;
	} else {
		if (interlace_seen) {
			changed = true;

		}
		interlace_seen = 0;
	}
	return changed;
}
