crossover_Probes(probe_combi_statistic *pcombi2)

{

    int rand_cross_pos1,
        rand_cross_pos2,
        rand_no_of_cross,
        random_intervall = mp_gl_awars.no_of_probes - 1;
    probe_combi_statistic *f1, *f2;

    rand_no_of_cross = random_intervall ? get_random(1, random_intervall) : 0;

    for (int i = 0; i < rand_no_of_cross; i++)
    {
        rand_cross_pos1 = get_random(0, random_intervall);
        rand_cross_pos2 = get_random(0, random_intervall);

        swap( & probe_combi[rand_cross_pos1], & pcombi2->probe_combi[rand_cross_pos2]);

        swap(  & probe_combi[rand_cross_pos1],  & probe_combi[random_intervall] );
        swap(  & pcombi2->probe_combi[rand_cross_pos2],  & pcombi2->probe_combi[random_intervall] );

        random_intervall--;
    }

    while (TRUE)
    {
        int change1, change2;

        f1 = check_duplicates();
        f2 = pcombi2->check_duplicates();

        if (f1 && f2 )
            break;

        if (f1)
            change1 = get_random(0,mp_gl_awars.no_of_probes - 1);
        else
            change1 = get_dupl_pos();

        if (f2)
            change2 = get_random(0,mp_gl_awars.no_of_probes - 1);
        else
            change2 = pcombi2->get_dupl_pos();

        swap( & probe_combi[change1],  & pcombi2->probe_combi[change2]);

    }

    init_stats();
    pcombi2->init_stats();
}
