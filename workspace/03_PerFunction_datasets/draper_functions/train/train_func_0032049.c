_PR_InitLinker(void)
{
    PRLibrary *lm = NULL;
#if defined(XP_UNIX)
    void *h;
#endif

    if (!pr_linker_lock) {
        pr_linker_lock = PR_NewNamedMonitor("linker-lock");
    }
    PR_EnterMonitor(pr_linker_lock);

#if defined(XP_PC)
    lm = PR_NEWZAP(PRLibrary);
    lm->name = strdup("Executable");
#if defined(XP_OS2)
    lm->dlh = NULLHANDLE;
#else

    lm->dlh = GetModuleHandle(NULL);
#endif

    lm->refCount    = 1;
    lm->staticTable = NULL;
    pr_exe_loadmap  = lm;
    pr_loadmap      = lm;

#elif defined(XP_UNIX)
#ifdef HAVE_DLL
#if defined(USE_DLFCN) && !defined(NO_DLOPEN_NULL)
    h = dlopen(0, RTLD_LAZY);
    if (!h) {
        char *error;

        DLLErrorInternal(_MD_ERRNO());
        error = (char*)PR_MALLOC(PR_GetErrorTextLength());
        (void) PR_GetErrorText(error);
        fprintf(stderr, "failed to initialize shared libraries [%s]\n",
            error);
        PR_DELETE(error);
        abort();
    }
#elif defined(USE_HPSHL)
    h = NULL;

#elif defined(USE_MACH_DYLD) || defined(NO_DLOPEN_NULL)
    h = NULL;
#else
#error no dll strategy
#endif

    lm = PR_NEWZAP(PRLibrary);
    if (lm) {
        lm->name = strdup("a.out");
        lm->refCount = 1;
        lm->dlh = h;
        lm->staticTable = NULL;
    }
    pr_exe_loadmap = lm;
    pr_loadmap = lm;
#endif
#endif

    if (lm) {
        PR_LOG(_pr_linker_lm, PR_LOG_MIN,
            ("Loaded library %s (init)", lm->name));
    }

    PR_ExitMonitor(pr_linker_lock);
}
