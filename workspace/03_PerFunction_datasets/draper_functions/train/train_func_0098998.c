cli_set_mode(int argc, char **argv, struct s_hardware *hardware)
{
    cli_mode_t new_mode;

    reset_more_printf();
    if (argc <= 0) {
	more_printf("Which mode?\n");
	return;
    }


    new_mode = mode_s_to_mode_t(argv[0]);
    set_mode(new_mode, hardware);
}
