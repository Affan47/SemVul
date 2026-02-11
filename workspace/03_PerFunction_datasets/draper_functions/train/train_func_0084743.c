opt_jumps_to_next_instruction(WsCompilerPtr compiler)
{
    WsAsmIns *i;
    WsBool change = WS_FALSE;

    ws_info(compiler, "optimize: jumps to next instruction");

    for (i = compiler->asm_head; i; i = i->next) {
        WsAsmIns * j;

        if (i->type != WS_ASM_P_JUMP)
            continue;

        for (j = i->next;
             j && j->type == WS_ASM_P_LABEL && i->ws_label != j;
             j = j->next)
            ;

        if (i->ws_label != j)

            continue;


        change = WS_TRUE;
        i->ws_label->ws_label_refcount--;

        if (i->next)
            i->next->prev = i->prev;
        else
            compiler->asm_tail = i->prev;

        if (i->prev)
            i->prev->next = i->next;
        else
            compiler->asm_head = i->next;


        i = j;
    }

    return change;
}
