jl_mark_box_caches(void)
{
    int64_t i;
    for(i=0; i < 256; i++) {
        jl_gc_markval(boxed_int8_cache[i]);
        jl_gc_markval(boxed_uint8_cache[i]);
    }
    for(i=0; i < NBOX_C; i++) {
        jl_gc_markval(boxed_int16_cache[i]);
        jl_gc_markval(boxed_int32_cache[i]);
        jl_gc_markval(boxed_int64_cache[i]);
        jl_gc_markval(boxed_uint16_cache[i]);
        jl_gc_markval(boxed_uint32_cache[i]);
        jl_gc_markval(boxed_char_cache[i]);
        jl_gc_markval(boxed_uint64_cache[i]);
    }
}
