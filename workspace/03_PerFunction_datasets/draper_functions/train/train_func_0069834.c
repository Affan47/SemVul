symb_updated_lines_set_from_map(void)
{
    int i, line;

    G_debug(2, "symb_updated_lines_set_from_map();");

    for (i = 0; i < Vect_get_num_updated_lines(&Map); i++) {
	line = Vect_get_updated_line(&Map, i);
	if (!Vect_line_alive(&Map, line))
	    continue;
	symb_line_set_from_map(line);
    }
}
