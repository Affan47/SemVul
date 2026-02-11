filter_rule_reset_stats(rule_t *rule)
{
    g_assert(rule != NULL);

    rule->match_count = rule->fail_count = 0;
}
