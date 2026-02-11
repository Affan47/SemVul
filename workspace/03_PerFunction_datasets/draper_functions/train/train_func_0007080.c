builtin_toggle_log(struct gp_event_t *ge)
{
    if (!ge)
	return "`builtin-toggle-log` y logscale for plots, z and cb for splots";

    if (volatile_data)
	int_warn(NO_CARET, "Cannot toggle log scale for volatile data");
    else if ((color_box.bounds.xleft < mouse_x && mouse_x < color_box.bounds.xright)
	 &&  (color_box.bounds.ybot  < mouse_y && mouse_y < color_box.bounds.ytop))
	do_string_replot( CB_AXIS.log ? "unset log cb" : "set log cb");
    else if (is_3d_plot && !splot_map)
	do_string_replot( Z_AXIS.log ? "unset log z" : "set log z");
    else
	do_string_replot( axis_array[FIRST_Y_AXIS].log ? "unset log y" : "set log y");

    return (char *) 0;
}
