vt_mallocwrap_init()
{

  mallocwrap_counter_group_id =
    vt_def_counter_group(VT_CURRENT_THREAD, "Memory");


  mallocwrap_counter_id =
    vt_def_counter(VT_CURRENT_THREAD, "Memory Allocation", "Bytes",
      VT_CNTR_ABS | VT_CNTR_NEXT, mallocwrap_counter_group_id, 0);


  if( (mallocwrap_write_markers = vt_env_memtrace_marker()) )
  {
    mallocwrap_marker_alloc_id =
      vt_def_marker(VT_CURRENT_THREAD, "Memory Allocation", VT_MARKER_HINT);
    mallocwrap_marker_free_id =
      vt_def_marker(VT_CURRENT_THREAD, "Memory Deallocation", VT_MARKER_HINT);
  }
}
