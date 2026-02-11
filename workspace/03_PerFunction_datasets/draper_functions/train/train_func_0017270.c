parameter_editor_add_paramspec(ParameterEditor *self, GParamSpec *spec) {
    const gchar *group;


    group = param_spec_get_group(spec);
    if (group) {
	if ((!self->previous_group) || strcmp((void *) group, self->previous_group))
	    parameter_editor_add_group_heading(self, group);
	if (self->previous_group)
	    g_free(self->previous_group);
	self->previous_group = g_strdup(group);
    }


    if (spec->value_type == G_TYPE_DOUBLE)
	parameter_editor_add_numeric(self, spec);

    else if (spec->value_type == G_TYPE_UINT)
	parameter_editor_add_numeric(self, spec);

    else if (spec->value_type == GDK_TYPE_COLOR)
	parameter_editor_add_color(self, spec);

    else if (spec->value_type == G_TYPE_BOOLEAN)
	parameter_editor_add_boolean(self, spec);

    else if (g_type_is_a (spec->value_type, G_TYPE_ENUM))
	parameter_editor_add_enum (self, spec);

    else
	g_log(G_LOG_DOMAIN, G_LOG_LEVEL_WARNING,
	      "Can't edit values of type %s",
	      g_type_name(spec->value_type));
}
