dot2_levels(graph_t * g)
{
    int ssize;
    char* s;
    graph_t *Xg =
	agopen("level assignment constraints", Agstrictdirected, 0);

    agautoinit(Xg, sizeof(Agraphinfo_t), sizeof(Agnodeinfo_t),
	       sizeof(Agedgeinfo_t));
    compile_samerank(g, 0);
    compile_nodes(g, Xg);
    compile_edges(g, Xg);
    compile_clusters(g, Xg);
    break_cycles(Xg);
    connect_components(Xg);
    if ((s = agget(g,"searchsize")))
	ssize = atoi (s);
    else
	ssize = -1;
    rank2(Xg, 1, INT_MAX, ssize);
    readout_levels(g, Xg);
}
