gs_vmreclaim(gs_dual_memory_t *dmem, bool global)
{

    i_ctx_t *i_ctx_p =
        (i_ctx_t *)((char *)dmem - offset_of(i_ctx_t, memory));
    gs_ref_memory_t *lmem = dmem->space_local;
    int code = context_state_store(i_ctx_p);
    gs_ref_memory_t *memories[5];
    gs_ref_memory_t *mem;
    int nmem, i;

    memories[0] = dmem->space_system;
    memories[1] = mem = dmem->space_global;
    nmem = 2;
    if (lmem != dmem->space_global)
        memories[nmem++] = lmem;
    for (i = nmem; --i >= 0;) {
        mem = memories[i];
        if (mem->stable_memory != (gs_memory_t *)mem)
            memories[nmem++] = (gs_ref_memory_t *)mem->stable_memory;
    }


    for (i = nmem; --i >= 0; )
        alloc_close_chunk(memories[i]);


    for (i = (global ? i_vm_system : i_vm_local);
         i < countof(dmem->spaces_indexed);
         ++i
         ) {
        gs_ref_memory_t *mem = dmem->spaces_indexed[i];

        if (mem == 0 || (i > 0 && mem == dmem->spaces_indexed[i - 1]))
            continue;
        if (mem->stable_memory != (gs_memory_t *)mem)
            ialloc_gc_prepare((gs_ref_memory_t *)mem->stable_memory);
        for (;; mem = &mem->saved->state) {
            ialloc_gc_prepare(mem);
            if (mem->saved == 0)
                break;
        }
    }


    {
        void *ctxp = i_ctx_p;
        gs_gc_root_t context_root;

        gs_register_struct_root((gs_memory_t *)lmem, &context_root,
                                &ctxp, "i_ctx_p root");
        GS_RECLAIM(&dmem->spaces, global);
        gs_unregister_root((gs_memory_t *)lmem, &context_root, "i_ctx_p root");
        i_ctx_p = ctxp;
        dmem = &i_ctx_p->memory;
    }


    *systemdict = *ref_stack_index(&d_stack, ref_stack_count(&d_stack) - 1);


    dicts_gc_cleanup();


    for (i = 0; i < nmem; ++i)
        alloc_open_chunk(memories[i]);


    code = context_state_load(i_ctx_p);

}
