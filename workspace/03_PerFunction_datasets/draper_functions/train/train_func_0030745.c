dwarf_print_memory_stats(Dwarf_Debug dbg)
{
    Dwarf_Alloc_Hdr alloc_hdr;
    Dwarf_Shalf i;


    char *alloc_type_name[MAX_DW_DLA + 1] = {
        "",
        "DW_DLA_STRING",
        "DW_DLA_LOC",
        "DW_DLA_LOCDESC",
        "DW_DLA_ELLIST",
        "DW_DLA_BOUNDS",
        "DW_DLA_BLOCK",
        "DW_DLA_DEBUG",
        "DW_DLA_DIE",
        "DW_DLA_LINE",
        "DW_DLA_ATTR",
        "DW_DLA_TYPE",
        "DW_DLA_SUBSCR",
        "DW_DLA_GLOBAL",
        "DW_DLA_ERROR",
        "DW_DLA_LIST",
        "DW_DLA_LINEBUF",
        "DW_DLA_ARANGE",
        "DW_DLA_ABBREV",
        "DW_DLA_FRAME_OP",
        "DW_DLA_CIE",
        "DW_DLA_FDE",
        "DW_DLA_LOC_BLOCK",
        "DW_DLA_FRAME_BLOCK",
        "DW_DLA_FUNC",
        "DW_DLA_TYPENAME",
        "DW_DLA_VAR",
        "DW_DLA_WEAK",
        "DW_DLA_ADDR",
        "DW_DLA_RANGES",
        "DW_DLA_ABBREV_LIST",
        "DW_DLA_CHAIN",
        "DW_DLA_CU_CONTEXT",
        "DW_DLA_FRAME",
        "DW_DLA_GLOBAL_CONTEXT",
        "DW_DLA_FILE_ENTRY",
        "DW_DLA_LINE_CONTEXT",
        "DW_DLA_LOC_CHAIN",
        "DW_DLA_HASH_TABLE",
        "DW_DLA_FUNC_CONTEXT",
        "DW_DLA_TYPENAME_CONTEXT",
        "DW_DLA_VAR_CONTEXT",
        "DW_DLA_WEAK_CONTEXT",
        "DW_DLA_PUBTYPES_CONTEXT",
        "DW_DLA_HASH_TABLE_ENTRY",
    };

    if (dbg == NULL)
        return;

    printf("Size of Dwarf_Debug        %4ld bytes\n",
        (long) sizeof(*dbg));
    printf("Size of Dwarf_Alloc_Hdr_s  %4ld bytes\n",
        (long) sizeof(struct Dwarf_Alloc_Hdr_s));
    printf("size of Dwarf_Alloc_Area_s %4ld bytes\n",
        (long) sizeof(struct Dwarf_Alloc_Area_s));

    printf("   Alloc Type                   Curr  Structs byt   str\n");
    printf("   ----------                   ----  ------- per   per\n");
    for (i = 1; i <= MAX_DW_DLA; i++) {
        int indx = index_into_allocated[i].ia_al_num;

        alloc_hdr = &dbg->de_alloc_hdr[indx];
        if (alloc_hdr->ah_bytes_one_struct != 1) {
            printf("%2d %-25s   %6d %8d %6d %6d\n",
                (int) i,
                alloc_type_name[i],
                (int) alloc_hdr->ah_chunks_allocated,
                (int) alloc_hdr->ah_struct_user_holds,
                (int) alloc_hdr->ah_bytes_malloc_per_chunk,
                (int) alloc_hdr->ah_structs_per_chunk);
        }
    }
}
