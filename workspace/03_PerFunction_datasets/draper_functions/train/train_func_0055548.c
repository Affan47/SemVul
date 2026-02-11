_add_pid(uint16_t *list, uint16_t pid)
{
    for (; *list && *list < pid; list++) ;

    for (; *list; list++) {
        uint16_t tmp = *list;
        *list = pid;
        pid = tmp;
    }
    *list = pid;
}
