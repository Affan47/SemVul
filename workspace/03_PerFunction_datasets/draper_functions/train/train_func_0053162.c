get_curr_task(int cpu, char *runqbuf)
{
        ulong curr_task;

        curr_task = ULONG(runqbuf + OFFSET(runqueue_cpu) +
                (SIZE(cpu_s) * cpu_idx(cpu)) + OFFSET(cpu_s_curr));

        if (IS_KVADDR(curr_task))
                return curr_task;
        else
                return NO_TASK;
}
