add_flag(int flag, const char *envs)
{
    int env = atoi(envs);
    if (flag < env)
        flag = env;
    if (flag < 1)
        flag = 1;
    return flag;
}
