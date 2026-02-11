create_my_derwin(WINDOW *parent)
{
    PAIR ul, lr;
    WINDOW *result = 0;

    if (getwindow(parent, &ul, &lr)) {
	result = derwin(parent, lines_of(ul, lr), cols_of(ul, lr), pair_of(ul));
	if (result != 0) {
	    fill_window(result, 'd');
	    add_window(parent, result);
	}
    }
    if (result == 0)
	result = parent;
    return result;
}
