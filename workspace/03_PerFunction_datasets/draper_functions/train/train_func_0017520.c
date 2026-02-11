main(int argc, char *argv[])
{

    struct GModule *module;
    struct Option *input, *vect;

    struct Cell_head window;
    int bot, right, t0, b0, l0, r0, clear = 0;
    double Rw_l, Rscr_wl;
    char *map_name = NULL, *v_name = NULL, *s_name = NULL;


    G_gisinit(argv[0]);


    G_putenv("GRASS_UI_TERM", "1");

    module = G_define_module();
    module->keywords = _("raster, landscape structure analysis, patch index");
    module->description =
	_("Interactive tool used to setup the sampling and analysis framework "
	 "that will be used by the other r.le programs.");

    input = G_define_standard_option(G_OPT_R_MAP);
    input->description = _("Raster map to use to setup sampling");

    vect = G_define_standard_option(G_OPT_V_INPUT);
    vect->key = "vect";
    vect->description = _("Vector map to overlay");
    vect->required = NO;

    if (G_parser(argc, argv))
	exit(EXIT_FAILURE);


    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    G_sleep_on_error(1);


    map_name = input->answer;
    v_name = vect->answer;
    s_name = NULL;


    get_pwd();


    if (R_open_driver() != 0)
	G_fatal_error("No graphics device selected");


    D_setup(1);

    Rw_l = (double)G_window_cols() / G_window_rows();


    G_get_set_window(&window);
    t0 = R_screen_top();
    b0 = R_screen_bot();
    l0 = R_screen_left();
    r0 = R_screen_rite();
    Rscr_wl = (double)(r0 - l0) / (b0 - t0);

    if (Rscr_wl > Rw_l) {
	bot = b0;
	right = l0 + (b0 - t0) * Rw_l;
    }

    else {
	right = r0;
	bot = t0 + (r0 - l0) / Rw_l;
    }
    D_new_window("a", t0, bot, l0, right);
    D_set_cur_wind("a");
    D_show_window(D_translate_color("green"));
    D_setup(clear);
    R_close_driver();


    set_map(map_name, v_name, s_name, window, t0, bot, l0, right);

    return (EXIT_SUCCESS);
}
