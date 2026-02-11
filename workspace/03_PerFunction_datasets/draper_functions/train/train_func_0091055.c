gog_axis_base_parent_changed (GogObject *child, gboolean was_set)
{
	GogAxisBase *axis_base = GOG_AXIS_BASE (child);

	if (was_set) {
		if (GOG_IS_AXIS (child))
			axis_base->axis = GOG_AXIS (child);
		else
			axis_base->axis = GOG_AXIS (child->parent);
		axis_base->chart = GOG_CHART (GOG_OBJECT (axis_base->axis)->parent);

	} else {
		axis_base->axis = NULL;
		axis_base->chart = NULL;
	}
	(GOG_OBJECT_CLASS (gab_parent_klass)->parent_changed) (child, was_set);
}
