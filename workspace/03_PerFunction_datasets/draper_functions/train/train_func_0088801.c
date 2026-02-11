inst_find_point(struct coord pos)
{
	struct inst *inst, *found;
	int best_dist = 0;
	int dist, i;

	found = NULL;
	FOR_ALL_INSTS(i, ip_frame, inst) {
		if (!inst->u.frame.active)
			continue;
		dist = gui_dist_frame_eye(inst, pos, draw_ctx.scale);
		if (dist >= 0 && (!found || best_dist > dist)) {
			found = inst;
			best_dist = dist;
		}
	}
	if (found)
		return found;

	FOR_ALL_INSTS(i, ip_vec, inst) {
		if (!inst->active || !inst->ops->distance)
			continue;
		dist = inst->ops->distance(inst, pos, draw_ctx.scale);
		if (dist >= 0 && (!found || best_dist > dist)) {
			found = inst;
			best_dist = dist;
		}
	}
	return found;
}
