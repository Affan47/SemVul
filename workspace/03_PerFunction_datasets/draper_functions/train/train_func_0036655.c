xml_to_state_rule(xnode_t *xn, void *data)
{
    enum filter_prop_state display = FILTER_PROP_STATE_UNKNOWN;
    enum filter_prop_state download = FILTER_PROP_STATE_UNKNOWN;
    const char *buf;
    rule_t *rule;
    filter_t *target, *filter = data;
    guint16 flags;
	int error;
	guint64 v;

    g_assert(xn != NULL);
    g_assert(xnode_element_name(xn) != NULL);
    g_assert(filter != NULL);
    g_assert(0 == ascii_strcasecmp(xnode_element_name(xn), NODE_RULE_STATE));

    buf = xnode_prop_get(xn, TAG_RULE_STATE_DISPLAY);
    if (buf != NULL) {
    	v = parse_number(buf, &error);
		if (error) {
			XML_PARSE_ERROR(TAG_RULE_STATE_DISPLAY);
			goto failure;
		}
        if (v <= MAX_FILTER_PROP_STATE || v == FILTER_PROP_STATE_IGNORE) {
            display = v;
		}
    }

    buf = xnode_prop_get(xn, TAG_RULE_STATE_DOWNLOAD);
    if (buf != NULL) {
    	v = parse_number(buf, &error);
		if (error) {
			XML_PARSE_ERROR(TAG_RULE_STATE_DOWNLOAD);
			goto failure;
		}
        if (v <= MAX_FILTER_PROP_STATE || v == FILTER_PROP_STATE_IGNORE) {
            download = v;
		}
    }

    buf = xnode_prop_get(xn, TAG_RULE_TARGET);
    if (NULL == buf) {
		XML_MISSING(TAG_RULE_TARGET);
		goto failure;
	}
    target = parse_target(buf, &error);
    if (error) {
		XML_PARSE_ERROR(TAG_RULE_TARGET);
		goto failure;
	}

    flags = get_rule_flags_from_xml(xn);
    rule = filter_new_state_rule(display, download, target, flags);
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
