setDecimalLocale(void)
{
	struct lconv *extlconv;

	extlconv = localeconv();

	if (*extlconv->decimal_point)
		decimal_point = strdup(extlconv->decimal_point);
	else
		decimal_point = ".";
	if (*extlconv->grouping && atoi(extlconv->grouping) > 0)
		grouping = strdup(extlconv->grouping);
	else
		grouping = "3";
	if (*extlconv->thousands_sep)
		thousands_sep = strdup(extlconv->thousands_sep);
	else if (*decimal_point != ',')
		thousands_sep = ",";
	else
		thousands_sep = ".";
}
