bf_call_function_read(void)
{
    struct cf_state *s = alloc_data(sizeof(struct cf_state));
    const char *line = dbio_read_string();
    const char *hdr = "bf_call_function data: fname = ";
    int hlen = strlen(hdr);

    if (!strncmp(line, hdr, hlen)) {
	line += hlen;
	if ((s->fnum = number_func_by_name(line)) == FUNC_NOT_FOUND)
	    errlog("CALL_FUNCTION: Unknown built-in function: %s\n", line);
	else if (read_bi_func_data(s->fnum, &s->data, pc_for_bi_func_data()))
	    return s;
    }
    return 0;
}
