gatom_set(t_gatom *x, t_symbol *s, int argc, t_atom *argv)
{
    t_atom oldatom = x->a_atom;
    int changed = 0;
    if (!argc) return;
    if (x->a_atom.a_type == A_FLOAT)
        x->a_atom.a_w.w_float = atom_getfloat(argv),
            changed = (x->a_atom.a_w.w_float != oldatom.a_w.w_float);
    else if (x->a_atom.a_type == A_SYMBOL)
        x->a_atom.a_w.w_symbol = atom_getsymbol(argv),
            changed = (x->a_atom.a_w.w_symbol != oldatom.a_w.w_symbol);
    if (changed)
        gatom_retext(x, 1);
    x->a_buf[0] = 0;
}
