template_match(t_template *x1, t_template *x2)
{
    int i;
    if (x1->t_n < x2->t_n)
        return (0);
    for (i = x2->t_n; i < x1->t_n; i++)
    {
        if (x1->t_vec[i].ds_type == DT_ARRAY ||
            x1->t_vec[i].ds_type == DT_LIST)
                return (0);
    }
    if (x2->t_n > x1->t_n)
        post("add elements...");
    for (i = 0; i < x2->t_n; i++)
        if (!dataslot_matches(&x1->t_vec[i], &x2->t_vec[i], 1))
            return (0);
    return (1);
}
