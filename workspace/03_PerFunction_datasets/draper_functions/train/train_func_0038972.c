gog_axis_calc_ticks (GogAxis *axis)
{
	g_return_if_fail (GOG_IS_AXIS (axis));

	if (axis->actual_map_desc->calc_ticks)
		axis->actual_map_desc->calc_ticks (axis);

	if (axis->type == GOG_AXIS_PSEUDO_3D || axis->type == GOG_AXIS_Z) {
		GSList *l;
		for (l = axis->contributors; l; l = l->next) {
			gog_plot_update_3d (GOG_PLOT (l->data));
		}
	}
}
