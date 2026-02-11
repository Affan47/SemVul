ecs_mem_free(void        *ptr,
             const char  *var_name,
             const char  *file_name,
             int          line_num)
{
  size_t  size_info;


  if (ptr == NULL)
    return NULL;


  if (_ecs_mem_global_initialized != 0) {

    size_info = _ecs_mem_block_size(ptr);

    _ecs_mem_global_alloc_cur -= size_info;

    if (_ecs_mem_global_file != NULL) {
      fprintf(_ecs_mem_global_file,"\n   free: %-27s:%6d : %-39s: %9lu",
              _ecs_mem_basename(file_name), line_num,
              var_name, (unsigned long)size_info);
      fprintf(_ecs_mem_global_file, " : (-%9lu) : %12lu : [%10p]",
              (unsigned long)size_info,
              (unsigned long)_ecs_mem_global_alloc_cur,
              ptr);
      fflush(_ecs_mem_global_file);
    }

    _ecs_mem_block_free(ptr);

    _ecs_mem_global_n_frees += 1;
  }

  free(ptr);

  return NULL;
}
