ws_asm_link(WsCompiler *compiler, WsAsmIns *ins)
{
    if (compiler->asm_tail) {
        compiler->asm_tail->next = ins;
        ins->prev = compiler->asm_tail;

        compiler->asm_tail = ins;
    } else
        compiler->asm_tail = compiler->asm_head = ins;
}
