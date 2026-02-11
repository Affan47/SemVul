throw_continuation(ScmObj *argframe, int nargs, void *data)
{
    ScmEscapePoint *ep = (ScmEscapePoint*)data;
    ScmObj args = argframe[0];
    ScmVM *vm = theVM;
    ScmObj handlers_to_call;

    if (ep->cstack && vm->cstack != ep->cstack) {
        ScmCStack *cs;
        for (cs = vm->cstack; cs; cs = cs->prev) {
            if (ep->cstack == cs) break;
        }


        if (cs != NULL) {
            vm->escapeReason = SCM_VM_ESCAPE_CONT;
            vm->escapeData[0] = ep;
            vm->escapeData[1] = args;
            siglongjmp(vm->cstack->jbuf, 1);
        }
    }

    handlers_to_call = throw_cont_calculate_handlers(ep, vm);
    return throw_cont_body(handlers_to_call, ep, args);
}
