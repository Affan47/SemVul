cpu_list_to_cpu_set(char *str, PLPA_NAME(cpu_set_t) *cpu_set)
{
    int ret;

    if (NULL == str) {
        return 1;
    }

    parser_setup_string(str);
    ret = token_parse(cpu_set);

    return ret;
}
