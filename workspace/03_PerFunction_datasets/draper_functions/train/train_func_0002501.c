iks_filter_packet (iksfilter *f, ikspak *pak)
{
	iksrule *rule, *max_rule;
	int fail, score, max_score;

	rule = f->rules;
	max_rule = NULL;
	max_score = 0;
	while (rule) {
		score = 0;
		fail = 0;
		if (rule->rules & IKS_RULE_TYPE) {
			if (rule->type == pak->type) score += 1; else fail = 1;
		}
		if (rule->rules & IKS_RULE_SUBTYPE) {
			if (rule->subtype == pak->subtype) score += 2; else fail = 1;
		}
		if (rule->rules & IKS_RULE_ID) {
			if (iks_strcmp (rule->id, pak->id) == 0) score += 16; else fail = 1;
		}
		if (rule->rules & IKS_RULE_NS) {
			if (iks_strcmp (rule->ns, pak->ns) == 0) score += 4; else fail = 1;
		}
		if (rule->rules & IKS_RULE_FROM) {
			if (pak->from && iks_strcmp (rule->from, pak->from->full) == 0) score += 8; else fail = 1;
		}
		if (rule->rules & IKS_RULE_FROM_PARTIAL) {
			if (pak->from && iks_strcmp (rule->from, pak->from->partial) == 0) score += 8; else fail = 1;
		}
		if (fail != 0) score = 0;
		rule->score = score;
		if (score > max_score) {
			max_rule = rule;
			max_score = score;
		}
		rule = rule->next;
	}
	while (max_rule) {
		if (IKS_FILTER_EAT == max_rule->filterHook (max_rule->user_data, pak)) return;
		max_rule->score = 0;
		max_rule = NULL;
		max_score = 0;
		rule = f->rules;
		while (rule) {
			if (rule->score > max_score) {
				max_rule = rule;
				max_score = rule->score;
			}
			rule = rule->next;
		}
	}
}
