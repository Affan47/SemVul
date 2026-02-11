construct_trapezoids(nseg)
int nseg;
{
    int i;
    int root, h;


    root = init_query_structure(choose_segment());

    for (i = 1; i <= nseg; i++)
        seg[i].root0 = seg[i].root1 = root;

    for (h = 1; h <= math_logstar_n(nseg); h++)
    {
        for (i = math_N(nseg, h -1) + 1; i <= math_N(nseg, h); i++)
            add_segment(choose_segment());


        for (i = 1; i <= nseg; i++)
            find_new_roots(i);
    }

    for (i = math_N(nseg, math_logstar_n(nseg)) + 1; i <= nseg; i++)
        add_segment(choose_segment());

    return 0;
}
