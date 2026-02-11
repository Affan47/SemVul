vg_rule_pattern_new (VgRule *rule)
{
	VgRulePattern *pat;
	VgCaller *c;

	pat = g_new (VgRulePattern, 1);
	pat->patterns = g_ptr_array_new ();
	pat->type = rule->type;
	pat->syscall = g_strdup (rule->syscall);

	c = rule->callers;
	while (c != NULL) {
		regex_t *regex;

		regex = g_new (regex_t, 1);

		if (regcomp (regex, c->name, REG_EXTENDED | REG_NOSUB) != 0) {
			g_free (regex);
			break;
		}

		g_ptr_array_add (pat->patterns, regex);

		c = c->next;
	}

	return pat;
}
