show_filemodify(struct diff_queue_struct *q,
			    struct diff_options *options, void *data)
{
	int i;


	qsort(q->queue, q->nr, sizeof(q->queue[0]), depth_first);

	for (i = 0; i < q->nr; i++) {
		struct diff_filespec *ospec = q->queue[i]->one;
		struct diff_filespec *spec = q->queue[i]->two;

		switch (q->queue[i]->status) {
		case DIFF_STATUS_DELETED:
			printf("D %s\n", spec->path);
			break;

		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			printf("%c \"%s\" \"%s\"\n", q->queue[i]->status,
			       ospec->path, spec->path);

			if (!hashcmp(ospec->sha1, spec->sha1) &&
			    ospec->mode == spec->mode)
				break;


		case DIFF_STATUS_TYPE_CHANGED:
		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_ADDED:


			if (no_data || S_ISGITLINK(spec->mode))
				printf("M %06o %s %s\n", spec->mode,
				       sha1_to_hex(spec->sha1), spec->path);
			else {
				struct object *object = lookup_object(spec->sha1);
				printf("M %06o :%d %s\n", spec->mode,
				       get_object_mark(object), spec->path);
			}
			break;

		default:
			die("Unexpected comparison status '%c' for %s, %s",
				q->queue[i]->status,
				ospec->path ? ospec->path : "none",
				spec->path ? spec->path : "none");
		}
	}
}
