ctrs_attach(ctr_list_t *list, pid_t pid, int cpu, int flags)
{
    for (ctr_t *cur = list->head; cur; cur = cur->next) {

        ctr_attach(cur, pid, cpu,
                   cur != list->head ? list->head->fd : -1,
                   flags);

        if (cur->fd == -1) {
            ctrs_close(list);
            return -1;
        }
    }

    return 0;
}
