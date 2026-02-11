genie_abend_all_threads (NODE_T * p, jmp_buf * jump_stat, NODE_T * label)
{
  (void) p;
  abend_all_threads = A68_TRUE;
  exit_from_threads = A68_FALSE;
  jump_buffer = jump_stat;
  jump_label = label;
  if (!is_main_thread ()) {
    genie_abend_thread ();
  }
}
