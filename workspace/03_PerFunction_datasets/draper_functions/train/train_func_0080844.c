gs_parse_real_file_name(gs_parsed_file_name_t * pfn, const char *pname,
                        uint len, gs_memory_t *mem, client_name_t cname)
{
    int code = gs_parse_file_name(pfn, pname, len, mem);

    if (code < 0)
        return code;
    if (pfn->len == 0)
        return_error(gs_error_undefinedfilename);
    return gs_terminate_file_name(pfn, mem, cname);
}
