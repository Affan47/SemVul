timer_callback(void* user_data) {
	blind_t* bp = user_data;

	check_time_limits(bp);


    if (is_field_solved(bp, bp->fieldnum))
        return 0;
	if (bp->cancelfname && file_exists(bp->cancelfname)) {
		bp->cancelled = TRUE;
		logmsg("File \"%s\" exists: cancelling.\n", bp->cancelfname);
		return 0;
	}
	return 1;
}
