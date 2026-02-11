graph_insert_into_new_columns(struct git_graph *graph,
					  struct commit *commit,
					  int *mapping_index)
{
	int i;


	for (i = 0; i < graph->num_new_columns; i++) {
		if (graph->new_columns[i].commit == commit) {
			graph->mapping[*mapping_index] = i;
			*mapping_index += 2;
			return;
		}
	}


	graph->new_columns[graph->num_new_columns].commit = commit;
	graph->mapping[*mapping_index] = graph->num_new_columns;
	*mapping_index += 2;
	graph->num_new_columns++;
}
