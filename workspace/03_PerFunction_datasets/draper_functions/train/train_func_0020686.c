source_progress_to_string(const struct download *d)
{
	static char buf[32];

	switch (d->status) {
	case GTA_DL_RECEIVING:
	case GTA_DL_IGNORING:
		str_bprintf(buf, sizeof buf, "%5.2f%%",
			100.0 * guc_download_source_progress(d));
		break;
	default:
		buf[0] = '\0';
	}
	return buf;
}
