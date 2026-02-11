token_pos_guess(const cst_item *token)
{
    const char *name = item_feat_string(token,"name");
    char *dc = cst_downcase(name);
    const cst_val *r;

    if (cst_regex_match(cst_rx_digits,dc))
	r = &val_string_numeric;
    else if ((cst_regex_match(cst_rx_double,dc)) ||
	(cst_regex_match(cst_rx_double,dc)))
	r = &val_string_number;
    else if (cst_streq(dc,"jan") ||
	cst_streq(dc,"january") ||
	cst_streq(dc,"feb") ||
	cst_streq(dc,"february") ||
	cst_streq(dc,"mar") ||
	cst_streq(dc,"march") ||
	cst_streq(dc,"apr") ||
	cst_streq(dc,"april") ||
	cst_streq(dc,"may") ||
	cst_streq(dc,"jun") ||
	cst_streq(dc,"june") ||
	cst_streq(dc,"jul") ||
	cst_streq(dc,"july") ||
	cst_streq(dc,"aug") ||
	cst_streq(dc,"august") ||
	cst_streq(dc,"sep") ||
	cst_streq(dc,"sept") ||
	cst_streq(dc,"september") ||
	cst_streq(dc,"oct") ||
	cst_streq(dc,"october") ||
	cst_streq(dc,"nov") ||
	cst_streq(dc,"november") ||
	cst_streq(dc,"dec") ||
	cst_streq(dc,"december"))
	r = &val_string_month;
    else if (cst_streq(dc,"sun") ||
	cst_streq(dc,"sunday") ||
	cst_streq(dc,"mon") ||
	cst_streq(dc,"monday") ||
	cst_streq(dc,"tue") ||
	cst_streq(dc,"tues") ||
	cst_streq(dc,"tuesday") ||
	cst_streq(dc,"wed") ||
	cst_streq(dc,"wednesday") ||
	cst_streq(dc,"thu") ||
	cst_streq(dc,"thurs") ||
	cst_streq(dc,"thursday") ||
	cst_streq(dc,"fri") ||
	cst_streq(dc,"friday") ||
	cst_streq(dc,"sat") ||
	cst_streq(dc,"saturday"))
	r = &val_string_day;

    else if (cst_streq(dc,"a"))
	r =  &val_string_a;
    else if (cst_streq(dc,"flight"))
	r =  &val_string_flight;
    else if (cst_streq(dc,"to"))
	r =  &val_string_to;
    else
	r =  &val_string_other;
    cst_free(dc);
    return r;
}
