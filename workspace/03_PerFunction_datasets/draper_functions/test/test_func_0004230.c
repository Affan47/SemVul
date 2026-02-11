fsnotify_find_mark(struct hlist_head *head,
					 struct fsnotify_group *group)
{
	struct fsnotify_mark *mark;

	hlist_for_each_entry(mark, head, obj_list) {
		if (mark->group == group) {
			fsnotify_get_mark(mark);
			return mark;
		}
	}
	return NULL;
}
