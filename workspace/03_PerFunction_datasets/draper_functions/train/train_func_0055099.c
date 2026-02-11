try_to_follow_renames(struct tree_desc *t1, struct tree_desc *t2, const char *base, struct diff_options *opt)
{
	struct diff_options diff_opts;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_filepair *choice;
	const char *paths[1];
	int i;


	choice = q->queue[0];
	q->nr = 0;

	diff_setup(&diff_opts);
	DIFF_OPT_SET(&diff_opts, RECURSIVE);
	DIFF_OPT_SET(&diff_opts, FIND_COPIES_HARDER);
	diff_opts.output_format = DIFF_FORMAT_NO_OUTPUT;
	diff_opts.single_follow = opt->paths[0];
	diff_opts.break_opt = opt->break_opt;
	paths[0] = NULL;
	diff_tree_setup_paths(paths, &diff_opts);
	if (diff_setup_done(&diff_opts) < 0)
		die("unable to set up diff options to follow renames");
	diff_tree(t1, t2, base, &diff_opts);
	diffcore_std(&diff_opts);
	diff_tree_release_paths(&diff_opts);


	opt->found_follow = 0;
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];


		if ((p->status == 'R' || p->status == 'C') && !strcmp(p->two->path, opt->paths[0])) {

			q->queue[i] = choice;
			choice = p;


			diff_tree_release_paths(opt);
			opt->paths[0] = xstrdup(p->one->path);
			diff_tree_setup_paths(opt->paths, opt);


			opt->found_follow = 1;
			break;
		}
	}


	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		diff_free_filepair(p);
	}


	q->queue[0] = choice;
	q->nr = 1;
}
