GC_push_selected(bottom, top, dirty_fn, push_fn)
ptr_t bottom;
ptr_t top;
int (*dirty_fn) GC_PROTO((struct hblk * h));
void (*push_fn) GC_PROTO((ptr_t bottom, ptr_t top));
{
    register struct hblk * h;

    bottom = (ptr_t)(((long) bottom + ALIGNMENT-1) & ~(ALIGNMENT-1));
    top = (ptr_t)(((long) top) & ~(ALIGNMENT-1));

    if (top == 0 || bottom == top) return;
    h = HBLKPTR(bottom + HBLKSIZE);
    if (top <= (ptr_t) h) {
  	if ((*dirty_fn)(h-1)) {
	    (*push_fn)(bottom, top);
	}
	return;
    }
    if ((*dirty_fn)(h-1)) {
        (*push_fn)(bottom, (ptr_t)h);
    }
    while ((ptr_t)(h+1) <= top) {
	if ((*dirty_fn)(h)) {
	    if ((word)(GC_mark_stack_top - GC_mark_stack)
		> 3 * GC_mark_stack_size / 4) {

		(*push_fn)((ptr_t)h, top);
		return;
	    } else {
		(*push_fn)((ptr_t)h, (ptr_t)(h+1));
	    }
	}
	h++;
    }
    if ((ptr_t)h != top) {
	if ((*dirty_fn)(h)) {
            (*push_fn)((ptr_t)h, top);
        }
    }
    if (GC_mark_stack_top >= GC_mark_stack_limit) {
        ABORT("unexpected mark stack overflow");
    }
}
