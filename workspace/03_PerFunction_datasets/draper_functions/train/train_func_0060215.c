load_server_protect_function_flags(void)
{
    int i;

    for (i = 0; i < top_bf_table; i++) {
	bf_table[i].protected
	    = server_flag_option(bf_table[i].protect_str, 0);
    }
    oklog("Loaded protect cache for %d builtin functions\n", i);
}
