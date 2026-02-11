atom_len_helper(Erl_Atom_data* a)
{
    if (erl_atom_ptr_latin1(a)) {
	return 1 + 2 + a->lenL;
    }
    else {
	return 1 + 1 + (a->lenU > 255) + a->lenU;
    }
}
