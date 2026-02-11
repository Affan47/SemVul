retain_small_bitmap (StgPtr p, nat size, StgWord bitmap,
		     StgClosure *c, retainer c_child_r)
{
    while (size > 0) {
	if ((bitmap & 1) == 0) {
	    retainClosure((StgClosure *)*p, c, c_child_r);
	}
	p++;
	bitmap = bitmap >> 1;
	size--;
    }
    return p;
}
