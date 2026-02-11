all_graph_data_missing (const int *list, int t, const double **Z)
{
    int i;

    for (i=1; i<=list[0]; i++) {
	if (!na(Z[list[i]][t])) {
	    return 0;
	}
    }

    return 1;
}
