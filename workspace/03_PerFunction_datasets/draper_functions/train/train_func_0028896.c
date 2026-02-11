tc_valloc(size_t size) __THROW {

  if (pagesize == 0) pagesize = getpagesize();
  void* result = do_memalign_or_cpp_memalign(pagesize, size);
  MallocHook::InvokeNewHook(result, size);
  return result;
}
