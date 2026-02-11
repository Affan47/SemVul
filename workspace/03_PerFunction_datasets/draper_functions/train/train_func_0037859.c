gth_filter_real_create_element (DomDomizable *base,
				DomDocument  *doc)
{
	GthFilter  *self;
	DomElement *element;

	g_return_val_if_fail (DOM_IS_DOCUMENT (doc), NULL);

	self = GTH_FILTER (base);
	element = dom_document_create_element (doc, "filter",
					       "id", gth_test_get_id (GTH_TEST (self)),
					       "name", gth_test_get_display_name (GTH_TEST (self)),
					       NULL);

	if (! gth_test_is_visible (GTH_TEST (self)))
		dom_element_set_attribute (element, "display", "none");

	if ((self->priv->test != NULL) && (gth_test_chain_get_match_type (self->priv->test) != GTH_MATCH_TYPE_NONE))
		dom_element_append_child (element, dom_domizable_create_element (DOM_DOMIZABLE (self->priv->test), doc));

	if (self->priv->limit_type != GTH_LIMIT_TYPE_NONE) {
		DomElement *limit;
		char       *value;

		value = g_strdup_printf ("%" G_GOFFSET_FORMAT, self->priv->limit);
		limit = dom_document_create_element (doc, "limit",
						     "value", value,
						     "type", _g_enum_type_get_value (GTH_TYPE_LIMIT_TYPE, self->priv->limit_type)->value_nick,
						     "selected_by", self->priv->sort_name,
						     "direction", (self->priv->sort_direction == GTK_SORT_ASCENDING ? "ascending" : "descending"),
						     NULL);
		g_free (value);

		dom_element_append_child (element, limit);
	}

	return element;
}
