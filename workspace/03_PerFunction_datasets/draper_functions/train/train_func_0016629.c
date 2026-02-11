Scm__RecordLoadStart(ScmObj load_file_path)
{
    ScmVM *vm = Scm_VM();
#ifdef HAVE_GETTIMEOFDAY
    if (SCM_VM_RUNTIME_FLAG_IS_SET(vm, SCM_COLLECT_LOAD_STATS)) {
        struct timeval t0;
        gettimeofday(&t0, NULL);
        vm->stat.loadStat =
            Scm_Acons(load_file_path,
                      Scm_MakeIntegerU(t0.tv_sec*1000000+t0.tv_usec),
                      vm->stat.loadStat);
    }
#endif
    if (SCM_VM_RUNTIME_FLAG_IS_SET(vm, SCM_LOAD_VERBOSE)) {
        int len = Scm_Length(PARAM_REF(vm, load_history));
        SCM_PUTZ(";;", 2, SCM_CURERR);
        while (len-- > 0) SCM_PUTC(' ', SCM_CURERR);
        Scm_Printf(SCM_CURERR, "Loading %A...\n", load_file_path);
    }
}
