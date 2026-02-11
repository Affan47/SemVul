add_crs(Octstr *os)
{
    long i;
    Octstr *nos;

    if (os == NULL)
        return;

    nos = octstr_format("%c", '\r');
    i = 0;
    while (i < octstr_len(os)) {
        if (octstr_get_char(os, i) == '\n') {
	    octstr_insert(os, nos, i);
            ++i;
        }
        ++i;
    }

    octstr_destroy(nos);
}
