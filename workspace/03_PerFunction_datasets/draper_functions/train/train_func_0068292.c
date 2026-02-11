GC_check_annotated_obj(ohdr)
register oh * ohdr;
{
    register ptr_t body = (ptr_t)(ohdr + 1);
    register word gc_sz = GC_size((ptr_t)ohdr);
    if (ohdr -> oh_sz + DEBUG_BYTES > gc_sz) {
        return((ptr_t)(&(ohdr -> oh_sz)));
    }
    if (ohdr -> oh_sf != (START_FLAG ^ (word)body)) {
        return((ptr_t)(&(ohdr -> oh_sf)));
    }
    if (((word *)ohdr)[BYTES_TO_WORDS(gc_sz)-1] != (END_FLAG ^ (word)body)) {
        return((ptr_t)((word *)ohdr + BYTES_TO_WORDS(gc_sz)-1));
    }
    if (((word *)body)[SIMPLE_ROUNDED_UP_WORDS(ohdr -> oh_sz)]
        != (END_FLAG ^ (word)body)) {
        return((ptr_t)((word *)body + SIMPLE_ROUNDED_UP_WORDS(ohdr -> oh_sz)));
    }
    return(0);
}
