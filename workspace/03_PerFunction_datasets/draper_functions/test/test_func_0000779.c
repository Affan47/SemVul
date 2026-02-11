print_state(int state)
{
    if (state)
        fprintf(verbose_file, "\n\n");
    if (SRconflicts[state] || RRconflicts[state])
        print_conflicts(state);
    fprintf(verbose_file, "state %d\n", state);
    print_core(state);
    print_nulls(state);
    print_actions(state);
}
