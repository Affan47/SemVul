estimate_usage(int work_count, work_t* works, int seconds) {
    int usrcpu = usrcpu_usage(work_count, works);
    int syscpu = syscpu_usage(work_count, works);
    int total = usrcpu + syscpu;
    REF("Predicted resource usage for the next %d seconds\n", seconds);
    REF("CPU usage\n");
    REF("\tuser:   about %d%%\n", 100 * usrcpu / MAX(total, cpucount()));
    REF("\tsystem: about %d%%\n", 100 * syscpu / MAX(total, cpucount()));
    REF("Memory usage\n");
    REF("\t%ld bytes\n", work_count * sizeof (pthread_t) + mem_usage(work_count, works));
    REF("Thread usage\n");
    REF("\ttotal:  %d\n", work_count + 1);
    REF("\tlocked: %d\n", 0);
}
