check_end(Task *task)
{
    int i;

    for (i = 1; i <= task->TaskNum; i++) {
        if (!in_IntSet(task->TaskF, i)) {
            return TRUE;
        }
    }
    return FALSE;
}
