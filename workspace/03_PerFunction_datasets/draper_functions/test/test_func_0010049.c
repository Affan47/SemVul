print_line_detail(char *prefix,
    int opcode,
    Dwarf_Unsigned address,
    unsigned long file,
    unsigned long line,
    unsigned long column,
    int is_stmt, int basic_block, int end_sequence,
    int prologue_end, int epilogue_begin, int isa,
    Dwarf_Unsigned discriminator)
{
    printf("%-15s %2d 0x%" DW_PR_XZEROS DW_PR_DUx " "
        "%2lu   %4lu %2lu   %1d %1d %1d",
        prefix,
        (int) opcode,
        (Dwarf_Unsigned) address,
        (unsigned long) file,
        (unsigned long) line,
        (unsigned long) column,
        (int) is_stmt, (int) basic_block, (int) end_sequence);
    if(discriminator || prologue_end || epilogue_begin || isa) {
        printf(" %1d", prologue_end);
        printf(" %1d", epilogue_begin);
        printf(" %1d", isa);
        printf(" 0x%" DW_PR_DUx , discriminator);
    }
    printf("\n");
}
