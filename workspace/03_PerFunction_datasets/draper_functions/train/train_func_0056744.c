genmoves_args(char *args, enum stone color, int played,
	      struct time_info *ti, bool binary_args)
{
	char *end = args + CMDS_SIZE;
	char *s = args + snprintf(args, CMDS_SIZE, "%s %d", stone2str(color), played);

	if (ti->dim == TD_WALLTIME) {
		s += snprintf(s, end - s, " %.3f %.3f %d %d",
			      ti->len.t.main_time, ti->len.t.byoyomi_time,
			      ti->len.t.byoyomi_periods, ti->len.t.byoyomi_stones);
	}
	s += snprintf(s, end - s, binary_args ? " @0\n" : "\n");
}
