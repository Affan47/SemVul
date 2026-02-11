list_add_sorted(struct lib_context *lc,
		struct list_head *to, struct list_head *new,
		int (*f_sort) (struct list_head * pos, struct list_head * new))
{
	struct list_head *pos;

	list_for_each(pos, to) {


		if (!f_sort || f_sort(pos, new))
			break;
	}


	list_add_tail(new, pos);
}
