randomCall (Operand *dest, Block *func, StackFrame *f, StaticLink *slink,
        const Value &thisptr, const std::vector<Value> &args, bool isclosure) {
    for (int i = args.size() - 1 ; i >= 0 ; i--) {
        stack[sp++] = args[i] ;
    }
    stack[sp++] = thisptr ;
    CodeSequence *oldcode = currentCode ;
    Instruction *oldir = ir ;
    StackFrame *oldframe ;
    StaticLink *oldstaticlink ;
    oldframe = frame ;
    oldstaticlink = staticLink ;
    frame = f ;
    staticLink = slink ;

    InterpretedBlock *iblock = static_cast<InterpretedBlock*>(func) ;

    currentCode = iblock->code ;
    ir = &currentCode->code[0] ;
    try {
        callFunction (dest, args.size() + 1, iblock, isclosure) ;
    } catch (...) {
        frame = oldframe ;
        staticLink = oldstaticlink ;
        currentCode = oldcode ;
        ir = oldir ;
        throw ;
    }
    frame = oldframe ;
    staticLink = oldstaticlink ;
    currentCode = oldcode ;
    ir = oldir ;
}
