getGroupsForRE(RuleElement *re)
{
    string key_str = getREKey(re);
    return rule_element_groups[key_str];
}
