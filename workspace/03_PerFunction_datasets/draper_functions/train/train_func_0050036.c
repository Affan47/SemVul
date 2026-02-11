prefs_matcher_set_criteria(const gint criteria)
{
	gint match_criteria = 0;

	switch (criteria) {
	case CRITERIA_FOUND_IN_ADDRESSBOOK:
		match_criteria = MATCH_ABOOK;
		break;
	case CRITERIA_ALL:
		match_criteria = MATCH_ALL;
		break;
	case CRITERIA_AGE_GREATER:
	case CRITERIA_AGE_LOWER:
	case CRITERIA_AGE_GREATER_HOURS:
	case CRITERIA_AGE_LOWER_HOURS:
		match_criteria = MATCH_AGE;
		break;
	case CRITERIA_SCORE_GREATER:
	case CRITERIA_SCORE_LOWER:
	case CRITERIA_SCORE_EQUAL:
		match_criteria = MATCH_SCORE;
		break;
	case CRITERIA_SIZE_GREATER:
	case CRITERIA_SIZE_SMALLER:
	case CRITERIA_SIZE_EQUAL:
		match_criteria = MATCH_SIZE;
		break;
	case CRITERIA_SUBJECT:
	case CRITERIA_FROM:
	case CRITERIA_TO:
	case CRITERIA_CC:
	case CRITERIA_TO_OR_CC:
	case CRITERIA_NEWSGROUPS:
	case CRITERIA_INREPLYTO:
	case CRITERIA_REFERENCES:
	case CRITERIA_HEADER:
		match_criteria = MATCH_HEADER;
		break;
	case CRITERIA_HEADERS_PART:
	case CRITERIA_BODY_PART:
	case CRITERIA_MESSAGE:
		match_criteria = MATCH_PHRASE;
		break;
	case CRITERIA_TEST:
		match_criteria = MATCH_TEST;
		break;
#if !GTK_CHECK_VERSION(3, 0, 0)
	case CRITERIA_COLORLABEL:
		match_criteria = MATCH_LABEL;
		break;
#endif
	case CRITERIA_TAG:
	case CRITERIA_TAGGED:
		match_criteria = MATCH_TAGS;
		break;
	case CRITERIA_UNREAD:
	case CRITERIA_NEW:
	case CRITERIA_MARKED:
	case CRITERIA_DELETED:
	case CRITERIA_REPLIED:
	case CRITERIA_FORWARDED:
	case CRITERIA_LOCKED:
	case CRITERIA_SPAM:
	case CRITERIA_HAS_ATTACHMENT:
	case CRITERIA_SIGNED:
		match_criteria = MATCH_FLAG;
		break;
	case CRITERIA_PARTIAL:
		match_criteria = MATCH_PARTIAL;
		break;
	case CRITERIA_IGNORE_THREAD:
	case CRITERIA_WATCH_THREAD:
		match_criteria = MATCH_THREAD;
		break;
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(matcher.criteria_combo),
				 match_criteria);

	switch(match_criteria) {
	case MATCH_HEADER:
		if(criteria != CRITERIA_HEADER)
			combobox_select_by_data(GTK_COMBO_BOX(
						matcher.headers_combo),
						criteria);
		break;
	case MATCH_AGE:
	case MATCH_SCORE:
	case MATCH_SIZE:
	case MATCH_FLAG:
		combobox_select_by_data(GTK_COMBO_BOX(
					matcher.match_combo), criteria);
		break;
	case MATCH_PHRASE:
	case MATCH_TAGS:
		combobox_select_by_data(GTK_COMBO_BOX(
					matcher.criteria_combo2), criteria);
		break;
	}
}
