manager_queue_rule_show(struct mansession *s, const struct message *m)
{
	const char *rule = astman_get_header(m, "Rule");
	const char *id = astman_get_header(m, "ActionID");
	struct rule_list *rl_iter;
	struct penalty_rule *pr_iter;

	astman_append(s, "Response: Success\r\n");
	if (!ast_strlen_zero(id)) {
		astman_append(s, "ActionID: %s\r\n", id);
	}

	AST_LIST_LOCK(&rule_lists);
	AST_LIST_TRAVERSE(&rule_lists, rl_iter, list) {
		if (ast_strlen_zero(rule) || !strcasecmp(rule, rl_iter->name)) {
			astman_append(s, "RuleList: %s\r\n", rl_iter->name);
			AST_LIST_TRAVERSE(&rl_iter->rules, pr_iter, list) {
				astman_append(s, "Rule: %d,%s%d,%s%d\r\n", pr_iter->time, pr_iter->max_relative && pr_iter->max_value >= 0 ? "+" : "", pr_iter->max_value, pr_iter->min_relative && pr_iter->min_value >= 0 ? "+" : "", pr_iter->min_value );
			}
			if (!ast_strlen_zero(rule)) {
				break;
			}
		}
	}
	AST_LIST_UNLOCK(&rule_lists);


	astman_append(s, "\r\n\r\n");

	return RESULT_SUCCESS;
}
