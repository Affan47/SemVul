main(int argc, char *argv[])
{
    char **args[2];
    int arg = 0;

    openconsole(&dev_null_r, &dev_stdcon_w);

    if (argc)
	arg++;
    args[0] = &argv[arg];
    args[1] = NULL;
    while (arg < argc) {
	if (!strcmp(argv[arg], "--")) {
	    argv[arg] = NULL;
	    args[1] = &argv[arg + 1];
	    break;
	}
	arg++;
    }
    if (args[1] != NULL) {
	boot_args(plop_INT13h_check()? args[0] : args[1]);
    } else {
	fprintf(stderr,
		"Usage:   ifplop.c32 [<plop_detected>] -- [<plop_not_detected>]\n"
		"Example: ifplop.c32 menu.c32 another.cfg -- plpbt hiddenusb usb1=2\n");
    }

    return 0;
}
