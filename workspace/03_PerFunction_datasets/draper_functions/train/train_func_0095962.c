blame_request(struct view *view, enum request request, struct line *line)
{
	enum open_flags flags = display[0] == view ? OPEN_SPLIT : OPEN_DEFAULT;
	struct blame *blame = line->data;

	switch (request) {
	case REQ_VIEW_BLAME:
		if (check_blame_commit(blame)) {
			string_copy(opt_ref, blame->commit->id);
			open_view(view, REQ_VIEW_BLAME, OPEN_REFRESH);
		}
		break;

	case REQ_PARENT:
		if (check_blame_commit(blame) &&
		    select_commit_parent(blame->commit->id, opt_ref))
			open_view(view, REQ_VIEW_BLAME, OPEN_REFRESH);
		break;

	case REQ_ENTER:
		if (!blame->commit) {
			report("No commit loaded yet");
			break;
		}

		if (view_is_displayed(VIEW(REQ_VIEW_DIFF)) &&
		    !strcmp(blame->commit->id, VIEW(REQ_VIEW_DIFF)->ref))
			break;

		if (!strcmp(blame->commit->id, NULL_ID)) {
			struct view *diff = VIEW(REQ_VIEW_DIFF);
			const char *diff_index_argv[] = {
				"git", "diff-index", "--root", "--patch-with-stat",
					"-C", "-M", "HEAD", "--", view->vid, NULL
			};

			if (!blame->commit->has_previous) {
				diff_index_argv[1] = "diff";
				diff_index_argv[2] = "--no-color";
				diff_index_argv[6] = "--";
				diff_index_argv[7] = "/dev/null";
			}

			if (!prepare_update(diff, diff_index_argv, NULL, FORMAT_DASH)) {
				report("Failed to allocate diff command");
				break;
			}
			flags |= OPEN_PREPARED;
		}

		open_view(view, REQ_VIEW_DIFF, flags);
		if (VIEW(REQ_VIEW_DIFF)->pipe && !strcmp(blame->commit->id, NULL_ID))
			string_copy_rev(VIEW(REQ_VIEW_DIFF)->ref, NULL_ID);
		break;

	default:
		return request;
	}

	return REQ_NONE;
}
