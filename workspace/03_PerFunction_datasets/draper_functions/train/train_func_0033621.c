buf_dump_freelist_sizes(int severity)
{
#ifdef ENABLE_BUF_FREELISTS
  int i;
  log(severity, LD_MM, "====== Buffer freelists:");
  for (i = 0; freelists[i].alloc_size; ++i) {
    uint64_t total = ((uint64_t)freelists[i].cur_length) *
      freelists[i].alloc_size;
    log(severity, LD_MM,
        U64_FORMAT" bytes in %d %d-byte chunks ["U64_FORMAT
        " misses; "U64_FORMAT" frees; "U64_FORMAT" hits]",
        U64_PRINTF_ARG(total),
        freelists[i].cur_length, (int)freelists[i].alloc_size,
        U64_PRINTF_ARG(freelists[i].n_alloc),
        U64_PRINTF_ARG(freelists[i].n_free),
        U64_PRINTF_ARG(freelists[i].n_hit));
  }
  log(severity, LD_MM, U64_FORMAT" allocations in non-freelist sizes",
      U64_PRINTF_ARG(n_freelist_miss));
#else
  (void)severity;
#endif
}
