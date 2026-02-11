mdsModel(vtx_data * graph, int nG)
{
    int i, j, e;
    float *Dij;
    int shift = 0;
    double delta;

    if (graph->ewgts == NULL)
	return 0;


    Dij = compute_weighted_apsp_packed(graph, nG);


    for (i = 0; i < nG; i++) {
	shift += i;
	for (e = 1; e < graph[i].nedges; e++) {
	    j = graph[i].edges[e];
	    if (j < i)
		continue;
	    delta += abs(Dij[i * nG + j - shift] - graph[i].ewgts[e]);
	    Dij[i * nG + j - shift] = graph[i].ewgts[e];
	}
    }
    if (Verbose) {
	fprintf(stderr, "mdsModel: delta = %f\n", delta);
    }
    return Dij;
}
