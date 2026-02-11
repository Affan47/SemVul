sigar_cpu_list_get(sigar_t *sigar, sigar_cpu_list_t *cpulist)
{
    FILE *fp;
    char buffer[BUFSIZ], cpu_total[BUFSIZ], *ptr;
    int core_rollup = sigar_cpu_core_rollup(sigar), i=0;
    sigar_cpu_t *cpu;

    if (!(fp = fopen(PROC_STAT, "r"))) {
        return errno;
    }


    (void)fgets(cpu_total, sizeof(cpu_total), fp);

    sigar_cpu_list_create(cpulist);


    while ((ptr = fgets(buffer, sizeof(buffer), fp))) {
        if (!strnEQ(ptr, "cpu", 3)) {
            break;
        }

        if (core_rollup && (i % sigar->lcpu)) {

            cpu = &cpulist->data[cpulist->number-1];
        }
        else {
            SIGAR_CPU_LIST_GROW(cpulist);
            cpu = &cpulist->data[cpulist->number++];
            SIGAR_ZERO(cpu);
        }

        get_cpu_metrics(sigar, cpu, ptr);

        i++;
    }

    fclose(fp);

    if (cpulist->number == 0) {

        cpu = &cpulist->data[cpulist->number++];
        SIGAR_ZERO(cpu);
        get_cpu_metrics(sigar, cpu, cpu_total);
    }

    return SIGAR_OK;
}
