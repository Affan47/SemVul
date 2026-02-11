clish_source_internal(const clish_shell_t *shell,
		      const lub_argv_t    *argv,
                      bool_t              stop_on_error)
{
    bool_t      result = BOOL_FALSE;
    const char *filename = lub_argv__get_arg(argv,0);
    struct  stat   fileStat;
    FILE *file;


    clish_shell_t *this = (clish_shell_t *)shell;


    if (0 == stat((char *) filename, &fileStat))
    {
        if (!S_ISDIR (fileStat.st_mode))
        {
           file = fopen(filename,"r");
           if (NULL != file)
           {


                result = clish_shell_push_file((clish_shell_t *) this, file, stop_on_error);
                if (BOOL_FALSE == result)
                {

                    fclose(file);
                }
            }
        }
    }
    return result;
}
