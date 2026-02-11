wait_other_stop(int child, int count)
{

    while (get_task_state(child) != 'T') sched_yield();
    printf("%03d child %d is STOPped\n", count, child);
}
