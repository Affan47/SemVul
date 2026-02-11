vmem_alloc(size_t size, int flags)
{
  vmem_t vm;


  if (flags & VMFL_NOZERO) {
    vm.mem = (char *) xmalloc(size);
  } else {
    vm.mem = (char *) xcalloc(size, 1);
  }
  vm.size = size;
  return vm;
}
