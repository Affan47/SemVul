zScoreDurationGroup(const zDurationGroup *dm, coor_t pos, float gc) {
	int iso_group;
	zDuration *duration;

	if (pos < 1) {
		zWarn("zScoreDurationGroup positive, non-zero integers only");
		return 0;
	}

	iso_group = zGetDurationIsochoreGroup(dm, gc);
	if ( iso_group < 0 || iso_group >= dm->durations ) {
		zWarn("zDurationGroup error: group index %d not found in %s", iso_group, zStrIdx2Char(dm->name) );
	}
	duration = &dm->duration[iso_group];

	return zScoreDuration(duration, pos);
}
