frame_fill_groups (call_frame_t *frame)
{
        char         filename[128];
        char         line[128];
        char        *ptr = NULL;
        int          ret = 0;
        FILE        *fp = NULL;
        int          idx = 0;
        long int     id = 0;
        char        *saveptr = NULL;
        char        *endptr = NULL;

        ret = snprintf (filename, 128, "/proc/%d/status", frame->root->pid);
        if (ret == 128)
                goto out;

        fp = fopen (filename, "r");
        if (!fp)
                goto out;

        while ((ptr = fgets (line, 128, fp))) {
                if (strncmp (ptr, "Groups:", 7) != 0)
                        continue;

                ptr = line + 8;

                for (ptr = strtok_r (ptr, " \t\r\n", &saveptr);
                     ptr;
                     ptr = strtok_r (NULL, " \t\r\n", &saveptr)) {
                        errno = 0;
                        id = strtol (ptr, &endptr, 0);
                        if (errno == ERANGE)
                                break;
                        if (!endptr || *endptr)
                                break;
                        frame->root->groups[idx++] = id;
                        if (idx == GF_REQUEST_MAXGROUPS)
                                break;
                }

                frame->root->ngrps = idx;
                break;
        }
out:
        if (fp)
                fclose (fp);
        return;
}
