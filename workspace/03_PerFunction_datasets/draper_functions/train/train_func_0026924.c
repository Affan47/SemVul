Scm__VMUnprotectStack(ScmVM *vm)
{
    SCM_ASSERT(vm->pc == PC_TO_RETURN);
    POP_CONT();
}
