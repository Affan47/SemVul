_clish_shell_spawn_and_wait(const clish_shell_hooks_t *hooks,
                            void                      *cookie,
                            FILE                      *file)
{
    void      *result = NULL;
    context_t *context = _clish_shell_spawn(NULL,hooks,cookie,file);

    if(context)
    {

        (void)pthread_join(context->pthread,&result);
    }
    return (int)result;
}
