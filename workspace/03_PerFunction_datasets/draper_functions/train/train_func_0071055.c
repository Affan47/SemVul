gGraphIsColorRuleRelative (const void *ptr, int *relative)
{

    gGraphColorRulePtr rule = (gGraphColorRulePtr) ptr;

    if (rule == NULL)
	return GGRAPH_INVALID_COLOR_RULE;
    if (rule->signature != GG_COLOR_RULE_MAGIC_SIGNATURE)
	return GGRAPH_INVALID_COLOR_RULE;

    if (rule->needs_range)
	*relative = GGRAPH_TRUE;
    else
	*relative = GGRAPH_FALSE;
    return GGRAPH_OK;
}
