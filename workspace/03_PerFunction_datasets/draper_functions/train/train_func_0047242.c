elm_quicklaunch_prepare(int    argc,
                        char **argv)
{
#ifdef HAVE_FORK
   char *exe;

   if (argc <= 0 || argv == NULL) return EINA_FALSE;

   exe = elm_quicklaunch_exe_path_get(argv[0]);
   if (!exe)
     {
        ERR("requested quicklaunch binary '%s' does not exist\n", argv[0]);
        return EINA_FALSE;
     }
   else
     {
        char *exe2, *p;
        char *exename;

        exe2 = malloc(strlen(exe) + 1 + 10);
        strcpy(exe2, exe);
        p = strrchr(exe2, '/');
        if (p) p++;
        else p = exe2;
        exename = alloca(strlen(p) + 1);
        strcpy(exename, p);
        *p = 0;
        strcat(p, "../lib/");
        strcat(p, exename);
        strcat(p, ".so");
        if (!access(exe2, R_OK | X_OK))
          {
             free(exe);
             exe = exe2;
          }
        else
          free(exe2);
     }
   qr_handle = dlopen(exe, RTLD_NOW | RTLD_GLOBAL);
   if (!qr_handle)
     {
        fprintf(stderr, "dlerr: %s\n", dlerror());
        WRN("dlopen('%s') failed: %s", exe, dlerror());
        free(exe);
        return EINA_FALSE;
     }
   INF("dlopen('%s') = %p", exe, qr_handle);
   qr_main = dlsym(qr_handle, "elm_main");
   INF("dlsym(%p, 'elm_main') = %p", qr_handle, qr_main);
   if (!qr_main)
     {
        WRN("not quicklauncher capable: no elm_main in '%s'", exe);
        dlclose(qr_handle);
        qr_handle = NULL;
        free(exe);
        return EINA_FALSE;
     }
   free(exe);
   return EINA_TRUE;
#else
   return EINA_FALSE;
   (void)argv;
#endif
}
