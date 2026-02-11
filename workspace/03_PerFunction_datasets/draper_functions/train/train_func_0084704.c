ck_process_stat_get_tty (CkProcessStat *stat)
{
        guint dev;
        char *tty;
        guint dev_maj;
        guint dev_min;
        pid_t pid;

        g_return_val_if_fail (stat != NULL, NULL);

        pid = stat->pid;
        dev = stat->tty;

        if (dev == 0u) {
                return NULL;
        }

        dev_maj = MAJOR_OF (dev);
        dev_min = MINOR_OF (dev);

        tty = link_name (dev_maj, dev_min, pid, "tty");
        if (tty != NULL) {
                goto out;
        }

        tty = driver_name (dev_maj, dev_min);
        if (tty != NULL) {
                goto out;
        }

        tty = link_name (dev_maj, dev_min, pid, "fd/2");
        if (tty != NULL) {
                goto out;
        }

        tty = link_name (dev_maj, dev_min, pid, "fd/255");
        if (tty != NULL) {
                goto out;
        }

 out:

        return tty;
}
