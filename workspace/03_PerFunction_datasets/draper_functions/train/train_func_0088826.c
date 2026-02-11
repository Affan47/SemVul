vxml_parser_set_element(vxml_parser_t *vp, const char *element, const char *ns)
{
	if (element != NULL) {
		const char *atom = vp->element;
		atom_str_change(&vp->element, element);
		if (atom != vp->element)
			vp->elem_token_valid = FALSE;
	} else {
		atom_str_free_null(&vp->element);
		vp->elem_token_valid = FALSE;
	}

	if (ns != NULL) {
		atom_str_change(&vp->namespace, ns);
	} else {
		atom_str_free_null(&vp->namespace);
	}

	if (vxml_debugging(19)) {
		const char *uri;
		const char *colon = vp->namespace ? ":" : "";

		uri = vxml_parser_namespace_uri(vp, vp->namespace);

		vxml_parser_debug(vp, "VXML current element: \"%s%s%s\" (%s)",
			NULL == vp->namespace ? "" : vp->namespace, colon,
			NULL == vp->element ? "(none)" : vp->element, uri);
	}
}
