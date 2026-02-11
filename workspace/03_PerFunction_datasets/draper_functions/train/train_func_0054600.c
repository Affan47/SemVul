abort_cpu_benchmarks() {
    int i;
    if (!benchmarks_running) return;
    for (i=0; i<bm_ncpus; i++) {
        abort_benchmark(benchmark_descs[i]);
    }
}
