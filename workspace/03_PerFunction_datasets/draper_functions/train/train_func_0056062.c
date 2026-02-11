duplicate()
{
    probe_tabs *new_obje = NULL;

    if (probe_tab)
        new_obje = probe_tab->duplicate();

    return new probe_combi_statistic(probe_combi, new_obje,expected_children, fitness, life_counter);
}
