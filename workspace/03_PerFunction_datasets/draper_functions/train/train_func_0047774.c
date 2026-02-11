init(int argc, char *argv[])
{
    char *pn;
    int seed;
    WINDOW *main_window;

#if !defined( ORIGINAL )
    getcwd(org_dir, 64);
#endif
    do_args(argc, argv);
    do_opts();

    pn = md_gln();
    if ((!pn) || (strlen(pn) >= 30)) {
	clean_up(mesg[13]);
    }
    (void) strcpy(login_name, pn);
    if (!nick_name[0]) {
	nick_name = login_name;
    }


    main_window = initscr();
    if (main_window == NULL) {
	return 1;
    }
    init_color_attr();

    if ((LINES < ROGUE_LINES) || (COLS < ROGUE_COLUMNS)) {
	clean_up(mesg[14]);
    }

    start_window();
    init_curses = 1;
    md_heed_signals();

    if (score_only) {
	message("", 0);
	put_scores((object *) 0, 0);
    }
    seed = md_gseed();
    (void) srrandom(seed);
#if !defined( ORIGINAL )
    if (do_restore && save_file && *save_file) {
	rest_file = save_file;
    }
#endif
    if (rest_file) {
	restore(rest_file);
	return (1);
    }
    mix_colors();
    get_wand_and_ring_materials();
    make_scroll_titles();

    level_objects.next_object = 0;
    level_monsters.next_monster = 0;
    player_init();
    party_counter = get_rand(1, PARTY_TIME);
    ring_stats(0);
    return 0;
}
