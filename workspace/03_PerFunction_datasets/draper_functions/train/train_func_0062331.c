zFreeDurationGroup(zDurationGroup *dm) {
	int i;

	for (i = 0; i < dm->durations; i++) {
		zFreeDuration(&dm->duration[i]);
	}
	zFree(dm->duration);  dm->duration  = NULL;
    zFree(dm->iso_bound); dm->iso_bound = NULL;
}
