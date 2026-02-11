go_pango_attr_superscript_new (gboolean val)
{
	GOPangoAttrSuperscript *result;

	static PangoAttrClass klass = {
		0,
		go_pango_attr_superscript_copy,
		go_pango_attr_destroy,
		go_pango_attr_superscript_compare
	};

	if (!klass.type)
		klass.type = go_pango_attr_superscript_get_attr_type ();

	result = g_new (GOPangoAttrSuperscript, 1);
	result->attr.klass = &klass;
	result->val = val;

	return (PangoAttribute *) result;
}
