poll_mirror_progress(struct cmd_context *cmd,
				struct logical_volume *lv, const char *name,
				struct daemon_parms *parms)
{
	percent_t segment_percent = PERCENT_0, overall_percent = PERCENT_0;
	uint32_t event_nr = 0;

	if (!lv_is_mirrored(lv) ||
	    !lv_mirror_percent(cmd, lv, !parms->interval, &segment_percent,
			       &event_nr) ||
	    (segment_percent == PERCENT_INVALID)) {
		log_error("ABORTING: Mirror percentage check failed.");
		return PROGRESS_CHECK_FAILED;
	}

	overall_percent = copy_percent(lv);
	if (parms->progress_display)
		log_print_unless_silent("%s: %s: %.1f%%", name, parms->progress_title,
					percent_to_float(overall_percent));
	else
		log_verbose("%s: %s: %.1f%%", name, parms->progress_title,
			    percent_to_float(overall_percent));

	if (segment_percent != PERCENT_100)
		return PROGRESS_UNFINISHED;

	if (overall_percent == PERCENT_100)
		return PROGRESS_FINISHED_ALL;

	return PROGRESS_FINISHED_SEGMENT;
}
