__spill_interval_intersecting(struct compilation_unit *cu,
					  struct live_interval *current,
					  enum machine_reg reg,
					  struct live_interval *it,
					  struct pqueue *unhandled)
{
	unsigned long start;

	if (it->reg != (int8_t) reg)
		return;

	if (!intervals_intersect(it, current))
		return;

	start = interval_intersection_start(current, it);
	if (start == interval_start(it))
		return;

	spill_interval(cu, it, start, unhandled);
}
