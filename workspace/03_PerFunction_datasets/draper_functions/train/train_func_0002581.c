Scm_DetachVM(ScmVM *vm)
{
#ifdef GAUCHE_HAS_THREADS
    if (vm != NULL) {
        SCM_INTERNAL_THREAD_SETSPECIFIC(Scm_VMKey(), NULL);
        vm_unregister(vm);
    }
#endif
}
