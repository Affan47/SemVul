vxml_parser_namespace_default(vxml_parser_t *vp, const char *value, size_t len)
{
	nv_pair_t *default_ns;

	if (vp->options & VXML_O_NO_NAMESPACES)
		return TRUE;


	default_ns = vxml_namespace_make(VXS_DEFAULT_NS, value, len);
	vxml_parser_namespace_insert(vp, default_ns, VXML_E_DUP_DEFAULT_NAMESPACE);

	return TRUE;
}
