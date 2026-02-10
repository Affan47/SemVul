makePolyline(graph_t* g, edge_t * e)
{
    Ppolyline_t spl, line = ED_path(e);
    Ppoint_t p0, q0;

    p0 = line.ps[0];
    q0 = line.ps[line.pn - 1];
    make_polyline (line, &spl);
    if (Verbose > 1)
	fprintf(stderr, "polyline %s %s\n", agnameof(agtail(e)), agnameof(aghead(e)));
    clip_and_install(e, aghead(e), spl.ps, spl.pn, &sinfo);
    addEdgeLabels(g, e, p0, q0);
}
