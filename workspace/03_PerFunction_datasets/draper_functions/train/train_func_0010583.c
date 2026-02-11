collect_compact(bool trace_contexts_p) {
  collect_mark_impl(trace_contexts_p);
  collect_compact_impl(trace_contexts_p);

  if (data->high_fragmentation_p()) {

    set_current_gc_op(collect_growing_heap_op);
    collect_growing_heap(0, trace_contexts_p);
  }

  code->flush_icache();
}
