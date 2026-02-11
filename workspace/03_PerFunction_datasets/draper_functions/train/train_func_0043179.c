GC_add_map_entry(sz)
word sz;
{
    register unsigned obj_start;
    register unsigned displ;
    register map_entry_type * new_map;
    word map_entry;

    if (sz > MAXOBJSZ) sz = 0;
    if (GC_obj_map[sz] != 0) {
        return(TRUE);
    }
    new_map = (map_entry_type *)GC_scratch_alloc(MAP_SIZE);
    if (new_map == 0) return(FALSE);
#   ifdef PRINTSTATS
        GC_printf1("Adding block map for size %lu\n", (unsigned long)sz);
#   endif
    for (displ = 0; displ < HBLKSIZE; displ++) {
        MAP_ENTRY(new_map,displ) = OBJ_INVALID;
    }
    if (sz == 0) {
        for(displ = 0; displ <= HBLKSIZE; displ++) {
            if (OFFSET_VALID(displ)) {
		map_entry = BYTES_TO_WORDS(displ);
		if (map_entry > MAX_OFFSET) map_entry = OFFSET_TOO_BIG;
                MAP_ENTRY(new_map,displ) = (map_entry_type)map_entry;
            }
        }
    } else {
        for (obj_start = 0;
             obj_start + WORDS_TO_BYTES(sz) <= HBLKSIZE;
             obj_start += WORDS_TO_BYTES(sz)) {
             for (displ = 0; displ < WORDS_TO_BYTES(sz); displ++) {
                 if (OFFSET_VALID(displ)) {
		     map_entry = BYTES_TO_WORDS(displ);
		     if (map_entry > MAX_OFFSET) map_entry = OFFSET_TOO_BIG;
                     MAP_ENTRY(new_map, obj_start + displ) =
						(map_entry_type)map_entry;
                 }
             }
        }
    }
    GC_obj_map[sz] = new_map;
    return(TRUE);
}
