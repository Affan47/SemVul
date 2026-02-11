get_env_value (const char *name_value, const char *name)
{
    int j;

    for (j = 0; name[j] && name_value[j] && name[j] == name_value[j]; j++);
    if (name[j] == '\0' && name_value[j] == '=')
        return &name_value[j + 1];

    return NULL;
}
