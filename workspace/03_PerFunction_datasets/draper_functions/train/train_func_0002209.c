recurse_vec(const char *name, const struct frame *frame,
    struct coord *res)
{
	const struct vec *v;

	if (!frame)
		return 0;
	for (v = frame->vecs; v; v = v->next)
		if (v->name == name) {
			*res = v->pos;
			return 1;
		}
	return recurse_vec(name, frame->curr_parent, res);
}
