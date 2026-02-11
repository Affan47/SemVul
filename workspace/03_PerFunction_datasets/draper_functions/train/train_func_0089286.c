remove_script_env(pos)
    int pos;
{
    free(script_env[pos] - 1);
    while ((script_env[pos] = script_env[pos + 1]) != NULL)
	pos++;
}
