gf_dash_get_timeline_duration(GF_MPD_SegmentTimeline *timeline, u32 *nb_segments, Double *max_seg_duration)
{
	u32 i, count;

	*nb_segments = 0;
	if (max_seg_duration) *max_seg_duration = 0;
	count = gf_list_count(timeline->entries);
	for (i=0; i<count; i++) {
		GF_MPD_SegmentTimelineEntry *ent = gf_list_get(timeline->entries, i);
		*nb_segments += 1 + ent->repeat_count;
		if (max_seg_duration && (*max_seg_duration < ent->duration)) *max_seg_duration = ent->duration;
	}
}
