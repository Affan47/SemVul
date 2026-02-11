binbuf_addbinbuf(t_binbuf *x, t_binbuf *y)
{
    t_binbuf *z = binbuf_new();
    int i;
    t_atom *ap;
    binbuf_add(z, y->b_n, y->b_vec);
    for (i = 0, ap = z->b_vec; i < z->b_n; i++, ap++)
    {
        char tbuf[MAXPDSTRING];
        switch (ap->a_type)
        {
        case A_FLOAT:
            break;
        case A_SEMI:
            SETSYMBOL(ap, gensym(";"));
            break;
        case A_COMMA:
            SETSYMBOL(ap, gensym(","));
            break;
        case A_DOLLAR:
            sprintf(tbuf, "$%d", ap->a_w.w_index);
            SETSYMBOL(ap, gensym(tbuf));
            break;
        case A_DOLLSYM:
            atom_string(ap, tbuf, MAXPDSTRING);
            SETSYMBOL(ap, gensym(tbuf));
            break;
        case A_SYMBOL:

            if (!strcmp(ap->a_w.w_symbol->s_name, ";"))
                SETSYMBOL(ap, gensym(";"));
            else if (!strcmp(ap->a_w.w_symbol->s_name, ","))
                SETSYMBOL(ap, gensym(","));
            break;
        default:
            bug("binbuf_addbinbuf");
        }
    }

    binbuf_add(x, z->b_n, z->b_vec);
}
