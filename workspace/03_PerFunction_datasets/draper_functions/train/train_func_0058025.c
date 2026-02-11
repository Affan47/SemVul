_dwarf_macro_stack_push_index(Dwarf_Debug dbg, Dwarf_Signed indx,
    struct macro_stack_s *ms)
{
    Dwarf_Signed *newbase;

    if (ms->next_to_use >= ms->max) {
        long new_size;

        if (ms->max == 0) {
            ms->max = STARTERMAX;
        }
        new_size = ms->max * 2;
        newbase =
            _dwarf_get_alloc(dbg, DW_DLA_STRING,
                new_size * sizeof(Dwarf_Signed));
        if (newbase == 0) {

            ms->was_fault = 1;
            return DW_DLV_ERROR;
        }
        if(ms->st_base) {
            memcpy(newbase, ms->st_base,
                ms->next_to_use * sizeof(Dwarf_Signed));
            dwarf_dealloc(dbg, ms->st_base, DW_DLA_STRING);
        }
        ms->st_base = newbase;
        ms->max = new_size;
    }
    ms->st_base[ms->next_to_use] = indx;
    ++ms->next_to_use;
    return DW_DLV_OK;
}
