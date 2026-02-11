compute_apsp_simple(vtx_data * graph, int n)
{


    int i;
    DistType *storage = N_GNEW(n * n, int);
    DistType **dij;
    Queue Q;

    dij = N_GNEW(n, DistType *);
    for (i = 0; i < n; i++) {
	dij[i] = storage + i * n;
    }
    mkQueue(&Q, n);
    for (i = 0; i < n; i++) {
	bfs(i, graph, n, dij[i], &Q);
    }
    freeQueue(&Q);
    return dij;
}
