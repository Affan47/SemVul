gfs2_sb_assigns(struct gfs2_sb *lsb, const char *strfield,
			   const char *val)
{
	checkassigns(strfield, lsb, sb_lockproto, val);
	checkassigns(strfield, lsb, sb_locktable, val);
	checkassigns(strfield, lsb, sb_uuid, val);

	return -1;
}
