parse_disc_data(int cmd, int argc, char **argv, int idx)
{
    if (argc >= idx + 3) {

        sscanf(argv[idx+1], "%d", &dlength);
        sscanf(argv[idx+2], "%d", &tcount);
        if (argc == idx + tcount + 3) {

            if (tcount > 0) {
                int i;
                foffset = calloc(tcount, sizeof(int));
                for (i = 0; i < tcount; i++) {
                    sscanf(argv[idx+3+i], "%d", &foffset[i]);
                }
            }
        } else {
            error_usage("track count is %d, but %d frame offset(s) specified", tcount, (argc - idx - 3));
        }
    } else {
        error_usage("the %s command requires at least two arguments", CMD_STR(cmd));
    }
}
