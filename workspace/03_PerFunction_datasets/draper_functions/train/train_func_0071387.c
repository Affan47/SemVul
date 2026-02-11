init_heap (void)
{
  int heap_a_size = A68_ALIGN (heap_size);
  int handle_a_size = A68_ALIGN (handle_pool_size);
  int frame_a_size = A68_ALIGN (frame_stack_size);
  int expr_a_size = A68_ALIGN (expr_stack_size);
  int total_size = A68_ALIGN (heap_a_size + handle_a_size + frame_a_size + 2 * expr_a_size);
  BYTE_T *core = (BYTE_T *) (A68_ALIGN_T *) malloc ((size_t) total_size);
  ABEND (core == NO_BYTE, ERROR_OUT_OF_CORE, NO_TEXT);
  heap_segment = &core[0];
  handle_segment = &heap_segment[heap_a_size];
  stack_segment = &handle_segment[handle_a_size];
  fixed_heap_pointer = A68_ALIGNMENT;
  temp_heap_pointer = total_size;
  frame_start = 0;
  frame_end = stack_start = frame_start + frame_a_size;
  stack_end = stack_start + expr_a_size;
}
