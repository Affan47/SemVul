cpu_benchmarks(BENCHMARK_DESC* bdp) {
    HOST_INFO host_info;
    int retval;
    double vax_mips, int_loops=0, int_time=0, fp_time;

    bdp->error_str[0] = '\0';
    host_info.clear_host_info();

#if defined(ANDROID) && defined(__arm__)


    if (strstr(gstate.host_info.p_features, " neon ")) {

        retval = android_neon::whetstone(host_info.p_fpops, fp_time, MIN_CPU_TIME);
    } else if (strstr(gstate.host_info.p_features, " vfp ")) {

        retval = android_vfp::whetstone(host_info.p_fpops, fp_time, MIN_CPU_TIME);
    } else {
        retval = whetstone(host_info.p_fpops, fp_time, MIN_CPU_TIME);
    }
#else
    retval = whetstone(host_info.p_fpops, fp_time, MIN_CPU_TIME);
#endif
    if (retval) {
        bdp->error = true;
        sprintf(bdp->error_str, "FP benchmark ran only %f sec; ignoring", fp_time);
        return 0;
    }
#ifdef _WIN32


    if (bdp->ordinal == 0) {
#endif
    retval = dhrystone(vax_mips, int_loops, int_time, MIN_CPU_TIME);
    if (retval) {
        bdp->error = true;
        sprintf(bdp->error_str, "Integer benchmark ran only %f sec; ignoring", int_time);
        return 0;
    }
    host_info.p_iops = vax_mips*1e6;
    host_info.p_membw = 1e9;
#ifdef _WIN32
    }
    bdp->host_info = host_info;
    bdp->int_loops = int_loops;
    bdp->int_time = int_time;
#else
    FILE* finfo;
    finfo = boinc_fopen(bdp->filename, "w");
    if (!finfo) return ERR_FOPEN;
    host_info.write_cpu_benchmarks(finfo);
    fclose(finfo);
#endif
    return 0;
}
