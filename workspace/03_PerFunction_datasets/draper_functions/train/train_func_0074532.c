cha_s_atom(chasen_cell_t * cell)
{
    if (atomp(cell))
	return s_atom_val(cell);


    cha_exit_file(1, "%s is not atom\n", cha_s_tostr(cell));
    return NILSYMBOL;
}
