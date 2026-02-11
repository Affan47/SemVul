dualtree_nearestneighbour(kdtree_t* xtree, kdtree_t* ytree, double maxdist2,
                               double** nearest_d2, int** nearest_ind,
							   int** count_in_range,
							   anbool notself) {
    int i, NY, NNY;


    dualtree_callbacks callbacks;
    rs_params params;


	assert(nearest_d2);
	assert(nearest_ind);

    memset(&callbacks, 0, sizeof(dualtree_callbacks));
    callbacks.decision = rs_within_range;
    callbacks.decision_extra = &params;
    callbacks.result = rs_handle_result;
    callbacks.result_extra = &params;


    NY = kdtree_n(ytree);
	memset(&params, 0, sizeof(params));
	params.xtree = xtree;
	params.ytree = ytree;
	params.notself = notself;
	params.d2 = maxdist2;

	params.count_in_range = NULL;
	if (count_in_range) {
	  if (!(*count_in_range)) {
		*count_in_range = (int*)calloc(NY, sizeof(int));
	  }
	  params.count_in_range = *count_in_range;
	}


    if (*nearest_d2)
        params.nearest_d2 = *nearest_d2;
    else
        params.nearest_d2 = malloc(NY * sizeof(double));

    if (maxdist2 == 0.0)
        maxdist2 = HUGE_VAL;
    for (i=0; i<NY; i++)
        params.nearest_d2[i] = maxdist2;


    if (*nearest_ind)
        params.nearest_ind = *nearest_ind;
    else
        params.nearest_ind = malloc(NY * sizeof(int));
    for (i=0; i<NY; i++)
        params.nearest_ind[i] = -1;

    NNY = kdtree_nnodes(ytree);
    params.node_nearest_d2 = malloc(NNY * sizeof(double));
    for (i=0; i<NNY; i++)
        params.node_nearest_d2[i] = maxdist2;

    dualtree_search(xtree, ytree, &callbacks);


	*nearest_d2 = params.nearest_d2;
	*nearest_ind = params.nearest_ind;
    free(params.node_nearest_d2);
}
