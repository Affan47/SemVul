operator delete(void *ptr, size_t size) throw ()
{
  if (ptr)
  {


    MEM_ROOT own_root= ((Ed_result_set*) ptr)->m_mem_root;
    free_root(&own_root, MYF(0));
  }
}
