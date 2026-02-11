gf_mpd_parse_segment_list(GF_MPD *mpd, GF_XMLNode *root)
{
	u32 i;
	GF_MPD_SegmentList *seg;
	GF_XMLAttribute *att;
	GF_XMLNode *child;

	GF_SAFEALLOC(seg, GF_MPD_SegmentList);
	if (!seg) return NULL;
	seg->segment_URLs = gf_list_new();

	i = 0;
	while ( (att = gf_list_enum(root->attributes, &i)) ) {
		if (strstr(att->name, "href")) seg->xlink_href = gf_mpd_parse_string(att->value);
		else if (strstr(att->name, "actuate")) seg->xlink_actuate_on_load = !strcmp(att->value, "onLoad") ? 1 : 0;
	}
	gf_mpd_parse_multiple_segment_base(mpd, (GF_MPD_MultipleSegmentBase *)seg, root);

	i = 0;
	while ( (child = gf_list_enum(root->content, &i))) {
		if (!gf_mpd_valid_child(mpd, child)) continue;
		if (!strcmp(child->name, "SegmentURL")) gf_mpd_parse_segment_url(seg->segment_URLs, child);
	}
	if (!gf_list_count(seg->segment_URLs)) {
		gf_list_del(seg->segment_URLs);
		seg->segment_URLs = NULL;
	}
	return seg;
}
