pfsize(Vmalloc_t * vm, Void_t * addr)
#else
static long pfsize(vm, addr)
Vmalloc_t *vm;
Void_t *addr;
#endif
{
    return (*Vmbest->addrf) (vm, addr) != 0 ? -1L : (long) PFSIZE(addr);
}
