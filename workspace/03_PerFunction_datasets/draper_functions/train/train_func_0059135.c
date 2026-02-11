isom_get_next_sap_time(GF_ISOFile *input, u32 track, u32 sample_count, u32 sample_num)
{
	GF_ISOSample *samp;
	u64 time;
	Bool is_rap, has_roll;
	u32 i, found_sample = 0;
	for (i=sample_num; i<=sample_count; i++) {
		if (gf_isom_get_sample_sync(input, track, i)) {
			found_sample = i;
			break;
		}
		gf_isom_get_sample_rap_roll_info(input, track, i, &is_rap, &has_roll, NULL);
		if (is_rap || has_roll) {
			found_sample = i;
			break;
		}
	}
	if (!found_sample) return 0;
	samp = gf_isom_get_sample_info(input, track, found_sample, NULL, NULL);
	time = samp->DTS;
	gf_isom_sample_del(&samp);
	return time;
}
