command_read(char *commandfile)
{


        FILE           *fp;
        char            buf[256];

        cmdval = 0;
        chdir(workdir);

        if (!strcmp(commandfile, HALTFILE)) {
                return CMD_STOP;
        }
        if (!strcmp(commandfile, KILLFILE)) {
                fp = fopen(commandfile, "r");
                fgets(buf, sizeof(buf) - 1, fp);
                cmdval = atoi(buf);
                fclose(fp);
                unlink(commandfile);
                return CMD_KILL;
        }
        if (!strcmp(commandfile, NICEFILE)) {
                fp = fopen(commandfile, "r");
                fgets(buf, sizeof(buf) - 1, fp);
                cmdval = atoi(buf);
                fclose(fp);
                unlink(commandfile);
                return CMD_RENICE;
        }
        return 0;
}
