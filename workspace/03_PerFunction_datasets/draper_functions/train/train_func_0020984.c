removeFromProfile(MethodBlock *mb, BasicBlock *block) {
    ProfileInfo *profile_info = block->u.profile.profiled;


    if(profile_info == NULL) {
        int ins_idx = block->length - 1;
        Instruction *ins = &block->start[ins_idx];
        PrepareInfo *prepare_info = ins->operand.pntr;
        OpcodeInfo *opcode_info = &block->opcodes[ins_idx];

        TRACE("Unwrapping non-quickened block (start %p)...\n", block->start);


        ins->operand = prepare_info->operand;
        MBARRIER();


        ins->handler = handler_entry_points[opcode_info->cache_depth]
                                           [opcode_info->opcode];

        sysFree(prepare_info);
        return;
    }

    TRACE("Removing block (start %p) from profile...\n", block->start);

    block->start->handler = profile_info->handler;

    if(profile_info->prev)
        profile_info->prev->next = profile_info->next;
    else
        mb->profile_info = profile_info->next;

    if(profile_info->next)
        profile_info->next->prev = profile_info->prev;

    sysFree(profile_info);
}
