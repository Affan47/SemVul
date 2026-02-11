gs_alloc_ref_array(gs_ref_memory_t * mem, ref * parr, uint attrs,
                   uint num_refs, client_name_t cname)
{
    ref *obj;


    if (mem->cc.rtop == mem->cc.cbot &&
        num_refs < (mem->cc.ctop - mem->cc.cbot) / sizeof(ref) &&
        mem->cc.rtop - (byte *) mem->cc.rcur + num_refs * sizeof(ref) <
        max_size_st_refs
        ) {
        ref *end;

        obj = (ref *) mem->cc.rtop - 1;
        if_debug4m('A', (const gs_memory_t *)mem, "[a%d:+$ ]%s(%u) = 0x%lx\n",
                   ialloc_trace_space(mem), client_name_string(cname),
                   num_refs, (ulong) obj);
        mem->cc.rcur[-1].o_size += num_refs * sizeof(ref);
        end = (ref *) (mem->cc.rtop = mem->cc.cbot +=
                       num_refs * sizeof(ref));
        make_mark(end - 1);
    } else {


        chunk_t *pcc = mem->pcc;
        ref *end;
        alloc_change_t *cp = 0;
        int code = 0;

        if ((gs_memory_t *)mem != mem->stable_memory) {
            code = alloc_save_change_alloc(mem, "gs_alloc_ref_array", &cp);
            if (code < 0)
                return code;
        }
        obj = gs_alloc_struct_array((gs_memory_t *) mem, num_refs + 1,
                                    ref, &st_refs, cname);
        if (obj == 0)
            return_error(e_VMerror);

        end = (ref *) obj + num_refs;
        make_mark(end);

        if (mem->pcc != pcc || mem->cc.cbot == (byte *) (end + 1)) {

            mem->cc.rcur = (obj_header_t *) obj;
            mem->cc.rtop = (byte *) (end + 1);
            mem->cc.has_refs = true;
        } else {


            chunk_locator_t cl;

            cl.memory = mem;
            cl.cp = mem->clast;
            chunk_locate_ptr(obj, &cl);
            cl.cp->has_refs = true;
        }
        if (cp) {
            mem->changes = cp;
            cp->where = (ref_packed *)obj;
        }
    }
    make_array(parr, attrs | mem->space, num_refs, obj);
    return 0;
}
