make_label(int frow, int fcol, NCURSES_CONST char *label)
{
    FIELD *f = new_field(1, (int) strlen(label), frow, fcol, 0, 0);

    if (f) {
	set_field_buffer(f, 0, label);
	set_field_opts(f, (int) (field_opts(f) & ~O_ACTIVE));
    }
    return (f);
}
