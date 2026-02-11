ecore_getopt_help(FILE               *fp,
                  const Ecore_Getopt *parser)
{
   const char *var;

   EINA_MAIN_LOOP_CHECK_RETURN;
   if (!parser) return;

   if (_argc < 1)
     {
        ecore_app_args_get(&_argc, &_argv);
        if ((_argc > 0) && (_argv[0]))
          prog = _argv[0];
        else
          prog = parser->prog;
     }

   var = getenv("COLUMNS");
   if (var)
     {
        cols = atoi(var);
        if (cols < 20)
          cols = 20;

        helpcol = cols / 3;
     }

   _ecore_getopt_help_usage(fp, parser);
   _ecore_getopt_help_description(fp, parser);
   _ecore_getopt_help_options(fp, parser);
}
