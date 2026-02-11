GC_has_other_debug_info(p)
ptr_t p;
{
    register oh * ohdr = (oh *)p;
    register ptr_t body = (ptr_t)(ohdr + 1);
    register word sz = GC_size((ptr_t) ohdr);

    if (HBLKPTR((ptr_t)ohdr) != HBLKPTR((ptr_t)body)
        || sz < DEBUG_BYTES + EXTRA_BYTES) {
        return(FALSE);
    }
    if (ohdr -> oh_sz == sz) {

    	return(FALSE);
    }
    if (ohdr -> oh_sf == (START_FLAG ^ (word)body)) return(TRUE);
    if (((word *)ohdr)[BYTES_TO_WORDS(sz)-1] == (END_FLAG ^ (word)body)) {
        return(TRUE);
    }
    return(FALSE);
}
