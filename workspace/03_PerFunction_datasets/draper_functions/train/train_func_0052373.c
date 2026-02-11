_dwarf_internal_globals_dealloc(Dwarf_Debug dbg, Dwarf_Global * dwgl,
    Dwarf_Signed count,
    int context_code,
    int global_code, int list_code)
{
    Dwarf_Signed i;
    struct Dwarf_Global_Context_s *gcp = 0;
    struct Dwarf_Global_Context_s *lastgcp = 0;

    for (i = 0; i < count; i++) {
        Dwarf_Global dgb = dwgl[i];

        gcp = dgb->gl_context;

        if (lastgcp != gcp) {
            lastgcp = gcp;
            dwarf_dealloc(dbg, gcp, context_code);
        }
        dwarf_dealloc(dbg, dgb, global_code);
    }
    dwarf_dealloc(dbg, dwgl, list_code);
    return;
}
