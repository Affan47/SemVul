cmd_truncate_file(double ratio, int halt_on_errors, int quiet,
                       char *output_dir, char **files,  char *msg)
{
    int i, n;

    char timer_buf[MAX_TIMER_LINE];
    time_t total_time;


    if (ratio == OPT_NA) {
        printf("You should specify truncation ratio\n");
        exit(1);
    } else if (ratio <= 1.0) {
        printf("Compression ratio must be greater than 1.0\n");
        exit(1);
    }

    n = get_number_of_files(files);

    if (!n) {
        printf("No input files\n");
        exit(1);
    }

    total_time = time(NULL);


    for (i = 0; i < n; i++) {
        truncate_file(ratio, halt_on_errors, quiet,
                      output_dir, files[i], i, n, msg);
    }

    total_time = time(NULL) - total_time;

    if (n > 1 && quiet == OPT_NO) {
        printf("Total %d file(s) done in %s\n",
            n, format_time((int)total_time, timer_buf, sizeof(timer_buf)));
    }
}
