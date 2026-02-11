save_set_new(gs_ref_memory_t * mem, bool to_new, bool set_limit, ulong *pscanned)
{
    ulong scanned = 0;
    int code;


    code = save_set_new_changes(mem, to_new, set_limit);
    if (code < 0)
        return code;


    SCAN_MEM_CHUNKS(mem, cp) {
        if (cp->has_refs) {
            bool has_refs = false;

            SCAN_CHUNK_OBJECTS(cp)
                DO_ALL
                if_debug3m('U', (gs_memory_t *)mem, "[U]set_new scan(0x%lx(%u), %d)\n",
                           (ulong) pre, size, to_new);
            if (pre->o_type == &st_refs) {

                ref_packed *prp = (ref_packed *) (pre + 1);
                uint size;

                code = mark_allocated(prp, to_new, &size);
                if (code < 0)
                    return code;
                scanned += size;
            } else
                scanned += sizeof(obj_header_t);
            END_OBJECTS_SCAN
                cp->has_refs = has_refs;
        }
    }
    END_CHUNKS_SCAN
    if_debug2m('u', (gs_memory_t *)mem, "[u]set_new (%s) scanned %ld\n",
               (to_new ? "restore" : "save"), scanned);
    *pscanned = scanned;
    return 0;
}
