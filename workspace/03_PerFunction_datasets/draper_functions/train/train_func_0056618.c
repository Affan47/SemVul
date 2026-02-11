xml_to_size_rule(xnode_t *xn, void *data)
{
    filter_t *target = NULL, *filter = data;
    filesize_t lower, upper;
    const char *buf;
    rule_t *rule;
    guint16 flags;
	int error;

    g_assert(xn != NULL);
    g_assert(xnode_element_name(xn) != NULL);
    g_assert(filter != NULL);
    g_assert(0 == ascii_strcasecmp(xnode_element_name(xn), NODE_RULE_SIZE));

    buf = xnode_prop_get(xn, TAG_RULE_SIZE_LOWER);
    if (buf == NULL) {
		XML_MISSING(TAG_RULE_SIZE_LOWER);
		goto failure;
	}
    lower = parse_number(buf, &error);
	if (error) {
		XML_PARSE_ERROR(TAG_RULE_SIZE_LOWER);
		goto failure;
	}

    buf = xnode_prop_get(xn, TAG_RULE_SIZE_UPPER);
    if (buf == NULL) {
		XML_MISSING(TAG_RULE_SIZE_UPPER);
		goto failure;
	}
    upper = parse_number(buf, &error);
	if (error) {
		XML_PARSE_ERROR(TAG_RULE_SIZE_UPPER);
		goto failure;
	}

    buf = xnode_prop_get(xn, TAG_RULE_TARGET);
    target = parse_target(buf, &error);
    if (error) {
		XML_PARSE_ERROR(TAG_RULE_TARGET);
		goto failure;
	}

    flags = get_rule_flags_from_xml(xn);
    rule = filter_new_size_rule(lower, upper, target, flags);
    rule->flags &= ~RULE_FLAG_VALID;

    if (GUI_PROPERTY(gui_debug) >= 4) {
        g_debug("added to filter \"%s\" rule with target %p",
            filter->name, cast_to_gconstpointer(rule->target));
	}

    filter->ruleset = g_list_append(filter->ruleset, rule);
	return;

failure:
	XML_BAD_NODE(xn);
}
