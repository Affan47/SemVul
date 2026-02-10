status_request(struct view *view, enum request request, struct line *line)
{
	struct status *status = line->data;

	switch (request) {
	case REQ_STATUS_UPDATE:
		if (!status_update(view))
			return REQ_NONE;
		break;

	case REQ_STATUS_MERGE:
		if (!status || status->status != 'U') {
			report("Merging only possible for files with unmerged status ('U').");
			return REQ_NONE;
		}
		open_mergetool(status->new.name);
		break;

	case REQ_EDIT:
		if (!status)
			return request;

		open_editor(status->status != '?', status->new.name);
		break;

	case REQ_VIEW_BLAME:
		if (status) {
			string_copy(opt_file, status->new.name);
			opt_ref[0] = 0;
		}
		return request;

	case REQ_ENTER:


		status_enter(view, line);
		return REQ_NONE;

	case REQ_REFRESH:

		break;

	default:
		return request;
	}

	open_view(view, REQ_VIEW_STATUS, OPEN_RELOAD);

	return REQ_NONE;
}
