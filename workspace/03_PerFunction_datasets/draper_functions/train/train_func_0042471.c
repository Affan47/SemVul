ws_asm_load_const(WsCompiler *compiler, WsUInt32 line,
                            WsUInt16 cindex)
{
    WsAsmIns *ins = asm_alloc(compiler, WS_ASM_P_LOAD_CONST, line);

    if (ins)
        ins->ws_cindex = cindex;

    return ins;
}
