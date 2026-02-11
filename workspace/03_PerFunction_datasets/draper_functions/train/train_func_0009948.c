scm_i_gc_grow_heap_p (scm_t_cell_type_statistics * freelist)
{
  return SCM_MAX (freelist->collected,freelist->collected_1)  < freelist->min_yield;
}
