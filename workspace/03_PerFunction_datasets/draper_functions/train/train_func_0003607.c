dupEnv(void)
{
    int i, l = arrLen(environ);
    char **env;
    if (!(env = Malloc((l + 1) * sizeof(char *))))
        return 0;
    for (i = 0; i < l; i++)
        strDup(env + i, environ[i]);
    env[i] = 0;
    return env;
}
