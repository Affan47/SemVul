tuple_intersect_size(jl_tuple_t *a, jl_tuple_t *b, int *bot)
{
    size_t al = a->length;
    size_t bl = b->length;
    *bot = 0;
    if (al == bl) return al;
    if (al > bl) return tuple_intersect_size(b, a, bot);
    assert(al < bl);
    if (jl_is_seq_type(jl_tupleref(b,bl-1))) {
        if (al > 0 && jl_is_seq_type(jl_tupleref(a,al-1))) {
            return bl;
        }
        else {
            if (bl == al+1)
                return al;
            *bot=1;
            return 0;
        }
    }
    if (al > 0 && jl_is_seq_type(jl_tupleref(a,al-1))) {
        return bl;
    }
    *bot=1;
    return 0;
}
