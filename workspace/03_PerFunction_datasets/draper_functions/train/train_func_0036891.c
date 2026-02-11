GC_post_incr (p, how_much)
GC_PTR *p;
size_t how_much;
{
    GC_PTR initial = *p;
    GC_PTR result = GC_same_obj((GC_PTR)((word)initial + how_much), initial);

    if (!GC_all_interior_pointers) {
    	(void) GC_is_valid_displacement(result);
    }
    *p = result;
    return(initial);
}
