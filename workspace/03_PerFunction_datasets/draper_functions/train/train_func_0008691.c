make_field(int frow, int fcol, int rows, int cols)
{
    FIELD *f = new_field(rows, cols, frow, fcol, o_value, 1);

    if (f) {
	set_field_back(f, A_UNDERLINE);


	set_field_just(f, j_value);
	if (d_option) {
	    if (has_colors()) {
		set_field_fore(f, COLOR_PAIR(2));
		set_field_back(f, A_UNDERLINE | COLOR_PAIR(3));
	    } else {
		set_field_fore(f, A_BOLD);
	    }


	    field_opts_off(f, O_STATIC);
	    set_max_field(f, m_value);
	}


	set_field_userptr(f, (void *) (long) field_back(f));
	if (t_value)
	    set_field_buffer(f, 0, t_value);
    }
    return (f);
}
