Scm_StartClassRedefinition(ScmClass *klass)
{
    int success = FALSE;
    ScmVM *vm;

    if (SCM_CLASS_CATEGORY(klass) != SCM_CLASS_SCHEME) {
        Scm_Error("cannot redefine class %S, which is not a Scheme-defined class", klass);
    }
    vm = Scm_VM();


    lock_class_redefinition(vm);


    (void)SCM_INTERNAL_MUTEX_LOCK(klass->mutex);
    if (SCM_FALSEP(klass->redefined)) {
        klass->redefined = SCM_OBJ(vm);
        success = TRUE;
    }
    (void)SCM_INTERNAL_MUTEX_UNLOCK(klass->mutex);

    if (!success) {
        unlock_class_redefinition(vm);
        Scm_Error("class %S seems abandoned during class redefinition", klass);
    }


    Scm_ClassMalleableSet(klass, TRUE);
}
