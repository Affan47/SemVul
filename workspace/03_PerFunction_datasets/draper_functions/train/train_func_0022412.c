vxml_parser_path_proper_ending(vxml_parser_t *vp)
{
	struct vxml_path_entry *pe;

	if (0 == vp->loc.depth) {
		vxml_fatal_error(vp, VXML_E_UNEXPECTED_TAG_END);
		return FALSE;
	}

	g_assert(vp->element != NULL);
	g_assert(uint_is_positive(vp->loc.depth));
	g_assert(uint_is_positive(vp->glob.depth));
	g_assert(vp->path != NULL);

	pe = vp->path->data;
	vxml_path_entry_check(pe);

	if (vxml_debugging(18)) {
		vxml_parser_debug(vp, "vxml_parser_path_proper_ending: "
			"would be leaving '%s' at depth %u (parsed \"%s\")",
			pe->element, vp->loc.depth, vp->element);
	}


	if (0 != strcmp(vp->element, pe->element)) {
		vxml_fatal_error(vp, VXML_E_INVALID_TAG_NESTING);
		return FALSE;
	}


	if (!(vp->options & VXML_O_NO_NAMESPACES)) {
		const char *start_uri = vxml_parser_namespace_uri(vp, pe->namespace);
		const char *end_uri = vxml_parser_namespace_uri(vp, vp->namespace);

		if (vxml_debugging(18)) {
			vxml_parser_debug(vp, "vxml_parser_path_proper_ending: "
				"leaving namespace '%s' at depth %u (parsed \"%s\")",
				start_uri, vp->loc.depth, end_uri);
		}

		if (0 != strcmp(start_uri, end_uri)) {
			vxml_fatal_error(vp, VXML_E_INVALID_TAG_NESTING);
			return FALSE;
		}
	}

	return TRUE;
}
