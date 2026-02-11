glade_property_dup_impl (GladeProperty *template_prop, GladeWidget *widget)
{
	GladeProperty *property;

	property          = g_object_new (GLADE_TYPE_PROPERTY,
					  "class", template_prop->klass,
					  "i18n-translatable", template_prop->i18n_translatable,
					  "i18n-has-context", template_prop->i18n_has_context,
					  "i18n-context", template_prop->i18n_context,
					  "i18n-comment", template_prop->i18n_comment,
					  NULL);
	property->widget  = widget;
	property->value   = g_new0 (GValue, 1);

	g_value_init (property->value, template_prop->value->g_type);


	if (template_prop->klass->parentless_widget)
	{
		if (!G_IS_PARAM_SPEC_OBJECT (template_prop->klass->pspec))
			g_warning ("Parentless widget property should be of object type");

		g_value_set_object (property->value, NULL);
	}
	else
		g_value_copy (template_prop->value, property->value);

	property->enabled = template_prop->enabled;
	property->state   = template_prop->state;

	glade_property_set_sensitive (property, template_prop->sensitive,
				      template_prop->insensitive_tooltip);

	return property;
}
