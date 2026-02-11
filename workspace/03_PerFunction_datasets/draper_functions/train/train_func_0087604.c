whitespace_rule(const char *pathname)
{
	struct git_attr_check attr_whitespace_rule;

	setup_whitespace_attr_check(&attr_whitespace_rule);
	if (!git_checkattr(pathname, 1, &attr_whitespace_rule)) {
		const char *value;

		value = attr_whitespace_rule.value;
		if (ATTR_TRUE(value)) {

			unsigned all_rule = 0;
			int i;
			for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++)
				if (!whitespace_rule_names[i].loosens_error &&
				    !whitespace_rule_names[i].exclude_default)
					all_rule |= whitespace_rule_names[i].rule_bits;
			return all_rule;
		} else if (ATTR_FALSE(value)) {

			return 0;
		} else if (ATTR_UNSET(value)) {

			return whitespace_rule_cfg;
		} else {

			return parse_whitespace_rule(value);
		}
	} else {
		return whitespace_rule_cfg;
	}
}
