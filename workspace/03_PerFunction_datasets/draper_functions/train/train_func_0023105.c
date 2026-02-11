get_dupl_pos()
{
    int length = mp_gl_awars.no_of_probes;

    for (int i=0; i<length-1; i++)
        if (probe_combi[i]->probe_index == probe_combi[i+1]->probe_index)
            return i;

    return -1;
}
