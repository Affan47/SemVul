ParsePolygon(p, tmp, pts, flag)
struct lex_record *p;
VPoint   *tmp;
VPoint   *pts;
int       flag;
{
	int       num_points, i, id;
	VPolygon  template;

	if (ParseColorInfo(p, flag) != 0) {
		ParseError(p, "invalid color specification");
		return 1;
	}

	template = *(pop_value(p, poly));

	if (NextToken(p) != TOKEN_LONG) {
		ParseError(p, "invalid polygon vertex count");
		return 1;
	}

	num_points = lex_value.long_value;

	for (i = 0; i < num_points; ++i) {
		if (NextToken(p) != TOKEN_LONG) {
			ParseError(p, "invalid polygon vertex");
			return 1;
		}
		id = lex_value.long_value;
		pts[i] = tmp[id - 1];
	}

	push_value(p, poly, VCreatePolygonFromTemplate(num_points, pts,
												   &template));
	return 0;
}
