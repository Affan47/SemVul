dump_read_format(void **data, uint16_t *size, struct perf_event_attr *attr)
{
    const uint64_t read_format = attr->read_format;
    dump_printf("  ---\n");
    if (!(read_format & PERF_FORMAT_GROUP)) {
        dump_printf("  value: %" PRIu64 "\n", read_uint64_t(data, size));
        if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED)
            dump_printf("  time_enabled: %" PRIu64 "\n", read_uint64_t(data, size));
        if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING)
            dump_printf("  time_running: %" PRIu64 "\n", read_uint64_t(data, size));
        if (read_format & PERF_FORMAT_ID)
            dump_printf("  id: %" PRIu64 "\n", read_uint64_t(data, size));
        dump_printf("  ---\n");
    } else {
        uint64_t nr = read_uint64_t(data, size);

        if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED)
            dump_printf("  time_enabled: %" PRIu64 "\n", read_uint64_t(data, size));
        if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING)
            dump_printf("  time_running: %" PRIu64 "\n", read_uint64_t(data, size));

        dump_printf("  ---\n");

        for (int i = 0; i < nr; i++) {
            dump_printf("  value: %" PRIu64 "\n", read_uint64_t(data, size));
            if (read_format & PERF_FORMAT_ID)
                dump_printf("  id: %" PRIu64 "\n", read_uint64_t(data, size));
            dump_printf("  ---\n");
        }
    }
}
