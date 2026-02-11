cb_auto_res_control(GkrellmChart *cp, guint option, GtkWidget* widget)
    {
    GkrellmChartconfig *cf;
	gint			grid_res;
	gboolean		active;

	cf = cp->config;
    switch (option)
        {
        case 0:
			cp->maxval_auto_base = 0;
			cp->maxval_peak = 0;
			break;
        case 1:
            active = GTK_CHECK_MENU_ITEM(widget)->active;
			cf->auto_resolution_stick = active;
			cp->maxval_auto_base = 0;
            break;
        case 2:
            active = GTK_CHECK_MENU_ITEM(widget)->active;
			if (cf->sequence_125 && active)
				return;
			cf->sequence_125 = active;
			break;
        case 3:
            active = GTK_CHECK_MENU_ITEM(widget)->active;
			if (!cf->sequence_125 && active)
				return;
			cf->sequence_125 = !active;

			grid_res = gkrellm_125_sequence(cf->grid_resolution,
						cf->sequence_125, cf->low, cf->high, TRUE, FALSE);
			cf->grid_resolution = grid_res;
			set_grid_resolution_spin_button(cp, grid_res);
            break;
        }
	gkrellm_refresh_chart(cp);
    }
