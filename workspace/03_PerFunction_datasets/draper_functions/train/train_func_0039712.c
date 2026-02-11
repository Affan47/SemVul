lock_dlobj(dlobj *dlo)
{
    ScmVM *vm = Scm_VM();
    (void)SCM_INTERNAL_MUTEX_LOCK(dlo->mutex);
    while (dlo->loader != vm) {
        if (dlo->loader == NULL) break;
        (void)SCM_INTERNAL_COND_WAIT(dlo->cv, dlo->mutex);
    }
    dlo->loader = vm;
    (void)SCM_INTERNAL_MUTEX_UNLOCK(dlo->mutex);
}
