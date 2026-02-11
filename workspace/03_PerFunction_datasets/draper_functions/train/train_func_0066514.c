poolsize(Vmalloc_t * vm, Void_t * addr)
#else
static long poolsize(vm, addr)
Vmalloc_t *vm;
Void_t *addr;
#endif
{
    return pooladdr(vm, addr) == 0 ? (long) vm->data->pool : -1L;
}
