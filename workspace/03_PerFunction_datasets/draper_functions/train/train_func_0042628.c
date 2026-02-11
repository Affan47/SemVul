command_label(argc, argv)
    int argc;
    char *argv[];
{
    if (argc == 1) {
	show_label(&current_book, -1);
    } else {
	show_label(&current_book, atoi(argv[1]) - 1);
    }

}
