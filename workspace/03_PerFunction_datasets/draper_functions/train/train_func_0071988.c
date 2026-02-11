fpreclass_get_default_cell_value(const struct FPReclass *r, DCELL cellVal)
{
    DCELL tmp;

    G_set_d_null_value(&tmp, 1);

    if ((cellVal < MIN(r->defaultDMin, r->defaultDMax)) ||
	(cellVal > MAX(r->defaultDMin, r->defaultDMax)))
	return tmp;

    if (r->defaultRRuleSet)
	return fpreclass_interpolate(r->defaultDMin, r->defaultDMax,
				     r->defaultRMin, r->defaultRMax, cellVal);
    else
	return fpreclass_interpolate(r->defaultDMin, r->defaultDMax,
				     DEFAULT_MIN, DEFAULT_MAX, cellVal);
}
