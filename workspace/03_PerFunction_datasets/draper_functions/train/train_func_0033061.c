usnob_get_survey_band(int survey) {

	switch (survey) {
	case USNOB_SURVEY_POSS_I_O:
		return 'O';
	case USNOB_SURVEY_POSS_I_E:
		return 'E';
	case USNOB_SURVEY_POSS_II_J:
	case USNOB_SURVEY_SERC_J:

		return 'J';
	case USNOB_SURVEY_POSS_II_F:
	case USNOB_SURVEY_ESO_R:

	case USNOB_SURVEY_AAO_R:
		return 'F';
	case USNOB_SURVEY_POSS_II_N:
	case USNOB_SURVEY_SERC_I:
	case USNOB_SURVEY_SERC_I_OR_POSS_II_N:
		return 'N';
	default:
		return '\0';
	}
}
