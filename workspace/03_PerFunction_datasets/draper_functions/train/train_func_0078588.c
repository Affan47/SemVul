listit(const char *funcname, int argc, char **argv)
{
    int i;
    krb5_error_code ret, saved_ret = 0;

    for (i = 0; i < argc; i++) {
	ret = foreach_principal(argv[i], do_list_entry, funcname, NULL);
        if (saved_ret == 0 && ret != 0)
            saved_ret = ret;
    }
    return saved_ret != 0;
}
