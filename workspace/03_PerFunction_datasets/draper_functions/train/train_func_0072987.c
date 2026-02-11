write_pidfile(const char *path, pid_t pid)
{
    FILE *file;

    file = fopen(path, "w");
    if (file == NULL) {
        syswarn("cannot create PID file %s", path);
        return;
    }
    if (fprintf(file, "%lu\n", (unsigned long) pid) < 0)
        syswarn("cannot write to PID file %s", path);
    if (fclose(file) == EOF)
        syswarn("cannot flush PID file %s", path);
}
