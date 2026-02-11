vmtruncate(Vmalloc_t * vm, Seg_t * seg, size_t size, int exact)
#else
static int vmtruncate(vm, seg, size, exact)
Vmalloc_t *vm;
Seg_t *seg;
size_t size;
int exact;
#endif
{
    reg Void_t *caddr;
    reg Seg_t *last;
    reg Vmdata_t *vd = vm->data;
    reg Vmemory_f memoryf = vm->disc->memoryf;

    caddr = seg->addr;

    if (size < seg->size) {
	reg size_t less;


	if ((less = vm->disc->round) <= 0)
	    less = _Vmpagesize;
	less = (size / less) * less;
	less = (less / ALIGN) * ALIGN;

	if (!exact)
	    less = (less / vd->incr) * vd->incr;

	if (less > 0 && size > less && (size - less) < sizeof(Block_t))
	    less -= vd->incr;

	if (less <= 0 ||
	    (*memoryf) (vm, caddr, seg->extent, seg->extent - less,
			vm->disc) != caddr)
	    return -1;

	seg->extent -= less;
	seg->size -= less;
	seg->baddr -= less;
	SIZE(BLOCK(seg->baddr)) = BUSY;
	return 0;
    }


    if (seg == vd->seg) {
	vd->seg = seg->next;
	last = NIL(Seg_t *);
    } else {
	for (last = vd->seg; last->next != seg; last = last->next);
	last->next = seg->next;
    }


    if ((*memoryf) (vm, caddr, seg->extent, 0, vm->disc) == caddr)
	return 0;


    if (last) {
	seg->next = last->next;
	last->next = seg;
    } else {
	seg->next = vd->seg;
	vd->seg = seg;
    }
    return -1;
}
