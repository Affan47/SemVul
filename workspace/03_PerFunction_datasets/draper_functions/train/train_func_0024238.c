print_event(FILE *out, const struct perf_event_attr *attr, uint64_t value)
{
    switch (attr->type) {
    case PERF_TYPE_HARDWARE:
        fprintf(out, "hw %" PRIu64 ": %" PRIu64 "\n",
                (uint64_t)attr->config, value);
        break;

    case PERF_TYPE_SOFTWARE:
        fprintf(out, "sw %" PRIu64 ": %" PRIu64 "\n",
                (uint64_t)attr->config, value);
        break;

    case PERF_TYPE_HW_CACHE:
        fprintf(out, "hwc 0x%" PRIx64 ": %" PRIu64 "\n",
                (uint64_t)attr->config, value);
        break;

    case PERF_TYPE_RAW:
        fprintf(out, "raw 0x%" PRIx64 ": %" PRIu64 "\n",
                (uint64_t)attr->config, value);
        break;

    default:
        fprintf(out, "unknown event (%" PRIu32 ":%" PRIu64 "): %" PRIu64 "\n",
                (uint32_t)attr->type, (uint64_t)attr->config, value);
        break;
    }
}
