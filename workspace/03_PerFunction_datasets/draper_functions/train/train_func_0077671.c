sigar_cpu_info_list_get(sigar_t *sigar,
                            sigar_cpu_info_list_t *cpu_infos)
{
    FILE *fp;
    int core_rollup = sigar_cpu_core_rollup(sigar), i=0;

    if (!(fp = fopen(PROC_FS_ROOT "cpuinfo", "r"))) {
        return errno;
    }

    (void)sigar_cpu_total_count(sigar);
    sigar_cpu_info_list_create(cpu_infos);

    while (get_cpu_info(sigar, &cpu_infos->data[cpu_infos->number], fp)) {
        sigar_cpu_info_t *info;

        if (core_rollup && (i++ % sigar->lcpu)) {
            continue;
        }

        info = &cpu_infos->data[cpu_infos->number];
        get_cpuinfo_max_freq(info, cpu_infos->number);
        get_cpuinfo_min_freq(info, cpu_infos->number);

        info->total_cores = sigar->ncpu;
        info->cores_per_socket = sigar->lcpu;
        info->total_sockets = sigar_cpu_socket_count(sigar);

        ++cpu_infos->number;
        SIGAR_CPU_INFO_LIST_GROW(cpu_infos);
    }

    fclose(fp);

    return SIGAR_OK;
}
