display_object(int col, int row, bool cursor, int oid)
{
	object_kind *kind = &k_info[oid];
	const char *inscrip = get_autoinscription(kind);

	char o_name[80];


	bool aware = (!kind->flavor || kind->aware);
	byte attr = curs_attrs[(int)aware][(int)cursor];


	bool use_flavour = (kind->flavor) && !(aware && kind->tval == TV_SCROLL);

	byte a = use_flavour ? kind->flavor->x_attr : kind->x_attr;
	byte c = use_flavour ? kind->flavor->x_char : kind->x_char;


	if (of_has(kind->flags, OF_INSTA_ART) && artifact_is_known(get_artifact_from_kind(kind)))
		get_artifact_display_name(o_name, sizeof(o_name), get_artifact_from_kind(kind));
	else
 		object_kind_name(o_name, sizeof(o_name), kind, OPT(cheat_know));


	if (kind->tried && !aware)
		my_strcat(o_name, " {tried}", sizeof(o_name));


	c_prt(attr, o_name, row, col);


	if ((aware && kind_is_squelched_aware(kind)) ||
		(!aware && kind_is_squelched_unaware(kind)))
		c_put_str(attr, "Yes", row, 46);


	if (aware && inscrip)
		c_put_str(TERM_YELLOW, inscrip, row, 55);

	if (tile_height == 1) {
		big_pad(76, row, a, c);
	}
}
