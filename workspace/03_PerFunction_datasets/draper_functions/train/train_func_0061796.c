launch_manual()
{
    char command[512];
    char *manual_file = find_manual_file();

    if (!manual_file) {
        fprintf(stderr, "No manual found.\n");
        return;
    }

#ifdef __APPLE__
    snprintf(command, sizeof(command), "%s/%s", get_data_dir(), manual_file);

    void open_file_with_browser_mac(char *file);

    open_file_with_browser_mac(command);
#else
    	switch (arch) {
        case ARCH_WETAB:
            snprintf(command, sizeof(command),
                "tiitoo-browser-bin -t file://%s/%s",
                get_data_dir(), manual_file);
            break;

        case ARCH_WIN32:
        case ARCH_WIN64:
            snprintf(command, sizeof(command),
                "%s", manual_file);
            break;

        default:
            if (!strcmp(options_browser, "browser")) {
                strcpy(options_browser, "./browser.sh");
            }
            snprintf(command, sizeof(command),
                "%s file://%s/%s",
                options_browser, get_data_dir(), manual_file);
            break;
    }

    launch_command(command);
#endif
}
