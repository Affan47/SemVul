main(int argc,
     char **argv)
{
   int i;

   for (i = 1; i < argc; i++)
     {
        if ((!strcmp(argv[i], "-h")) ||
            (!strcmp(argv[i], "-help")) ||
            (!strcmp(argv[i], "--help")))
          {
             printf(
               "This is an internal tool for Enlightenment.\n"
               "do not use it.\n"
               );
             exit(0);
          }
        else if (!strncmp(argv[i], "--nice=", 7))
          {
             const char *val;

             val = argv[i] + 7;
             if (*val)
               nice(atoi(val));
          }
     }

   ecore_init();
   ecore_app_args_set(argc, (const char **)argv);
   eet_init();
   evas_init();
   ecore_evas_init();
   edje_init();
   ecore_file_init();
   ecore_ipc_init();

   e_user_dir_concat_static(_thumbdir, "fileman/thumbnails");
   ecore_file_mkpath(_thumbdir);

   if (_e_ipc_init()) ecore_main_loop_begin();

   if (_e_ipc_server)
     {
        ecore_ipc_server_del(_e_ipc_server);
        _e_ipc_server = NULL;
     }

   ecore_ipc_shutdown();
   ecore_file_shutdown();
   ecore_evas_shutdown();
   edje_shutdown();
   evas_shutdown();
   eet_shutdown();
   ecore_shutdown();

   return 0;
}
