createClientLog(const char *log)
{
    char randstr[32], *randstrp = 0, *lname;
    int lfd;

    for (;;) {
        struct expando macros[] = {
            { 'd', 0, td->name },
            { 'u', 0, curuser },
            { 'r', 0, randstrp },
            { 0, 0, 0 }
        };
        if (!(lname = expandMacros(log, macros)))
            exit(1);
        unlink(lname);
        if ((lfd = open(lname, O_WRONLY|O_CREAT|O_EXCL, 0600)) >= 0) {
            dup2(lfd, 1);
            dup2(lfd, 2);
            close(lfd);
            free(lname);
            return True;
        }
        if (errno != EEXIST || !macros[2].uses) {
            free(lname);
            return False;
        }
        logInfo("Session log file %s not usable, trying another one.\n",
                lname);
        free(lname);
        sprintf(randstr, "%d", secureRandom());
        randstrp = randstr;
    }
}
