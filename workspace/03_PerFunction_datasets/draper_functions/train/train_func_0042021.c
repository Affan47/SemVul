gtemplate_free(t_gtemplate *x)
{

    t_template *t = x->x_template;
    t_gtemplate *y;
    if (x == t->t_list)
    {
        canvas_redrawallfortemplate(t, 2);
        if (x->x_next)
        {


            t_template *z = template_new(&s_,
                x->x_next->x_argc, x->x_next->x_argv);
            template_conform(t, z);
            pd_free(&t->t_pdobj);
            pd_free(&z->t_pdobj);
            z = template_new(x->x_sym, x->x_next->x_argc, x->x_next->x_argv);
            z->t_list = x->x_next;
            for (y = z->t_list; y ; y = y->x_next)
                y->x_template = z;
        }
        else t->t_list = 0;
        canvas_redrawallfortemplate(t, 1);
    }
    else
    {
        t_gtemplate *x2, *x3;
        for (x2 = t->t_list; x3 = x2->x_next; x2 = x3)
        {
            if (x == x3)
            {
                x2->x_next = x3->x_next;
                break;
            }
        }
    }
    freebytes(x->x_argv, sizeof(t_atom) * x->x_argc);
}
