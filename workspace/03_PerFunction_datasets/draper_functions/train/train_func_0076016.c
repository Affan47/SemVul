sigbiquad_list(t_sigbiquad *x, t_symbol *s, int argc, t_atom *argv)
{
    t_float fb1 = atom_getfloatarg(0, argc, argv);
    t_float fb2 = atom_getfloatarg(1, argc, argv);
    t_float ff1 = atom_getfloatarg(2, argc, argv);
    t_float ff2 = atom_getfloatarg(3, argc, argv);
    t_float ff3 = atom_getfloatarg(4, argc, argv);
    t_float discriminant = fb1 * fb1 + 4 * fb2;
    t_biquadctl *c = x->x_ctl;
    if (discriminant < 0)
    {


        if (fb2 >= -1.0f) goto stable;
    }
    else
    {


        if (fb1 <= 2.0f && fb1 >= -2.0f &&
            1.0f - fb1 -fb2 >= 0 && 1.0f + fb1 - fb2 >= 0)
                goto stable;
    }

    fb1 = fb2 = ff1 = ff2 = ff3 = 0;
stable:
    c->c_fb1 = fb1;
    c->c_fb2 = fb2;
    c->c_ff1 = ff1;
    c->c_ff2 = ff2;
    c->c_ff3 = ff3;
}
