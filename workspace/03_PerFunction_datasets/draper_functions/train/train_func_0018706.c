theil_forecast_plot (const int *plotlist, const DATASET *dset,
			 gretlopt opt)
{
    FILE *fp = NULL;
    gnuplot_info gi;
    int vx, vy;
    int err = 0;

    gretl_error_clear();

    if (plotlist[0] != 2) {
	return E_DATA;
    }

    err = gpinfo_init(&gi, opt | OPT_S, plotlist, NULL, dset);
    if (err) {
	goto bailout;
    }


    gi.flags &= ~GPT_TS;

    err = graph_list_adjust_sample(gi.list, &gi, dset, 1);
    if (err) {
	goto bailout;
    }

    fp = open_gp_stream(PLOT_REGULAR, gi.flags, &err);
    if (err) {
	goto bailout;
    }

    vx = gi.list[2];
    vy = gi.list[1];

    print_axis_label('x', series_get_graph_name(dset, vx), fp);
    print_axis_label('y', series_get_graph_name(dset, vy), fp);

    fputs("set xzeroaxis\n", fp);
    gnuplot_missval_string(fp);
    fputs("set key left top\n", fp);

    gretl_push_c_numeric_locale();

    print_x_range_from_list(&gi, dset, gi.list, fp);

    fputs("plot \\\n", fp);
    fputs(" '-' using 1:($2) notitle w points , \\\n", fp);
    fprintf(fp, " x title \"%s\" w lines\n", _("actual = predicted"));

    print_gp_data(&gi, dset, fp);

    gretl_pop_c_numeric_locale();

    err = finalize_plot_input_file(fp);

 bailout:

    clear_gpinfo(&gi);

    return err;
}
