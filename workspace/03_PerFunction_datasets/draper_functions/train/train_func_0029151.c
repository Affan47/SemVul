filter_is_accepted(const seaudit_filter_t * filter, const seaudit_message_t * msg)
{
	bool tried_criterion = false;
	int acceptval;
	size_t i;

	for (i = 0; i < sizeof(filter_criteria) / sizeof(filter_criteria[0]); i++) {
		if (filter_criteria[i].is_set(filter)) {
			tried_criterion = true;
			if (filter_criteria[i].support(msg)) {
				acceptval = filter_criteria[i].accept(filter, msg);
			} else if (filter->strict) {


				acceptval = 0;
			} else {


				continue;
			}
			if (filter->match == SEAUDIT_FILTER_MATCH_ANY && acceptval == 1) {
				return 1;
			}
			if (filter->match == SEAUDIT_FILTER_MATCH_ALL && acceptval == 0) {
				return 0;
			}
		}
	}
	if (!tried_criterion) {

		if (filter->strict) {

			return 0;
		}
		return 1;
	}
	if (filter->match == SEAUDIT_FILTER_MATCH_ANY) {

		return 0;
	}

	return 1;
}
