cb_Graph_Statistics_AdjacencyMatrix (wxCommandEvent &event)
{
	MatrixDialog md (this, _("Adjacency Matrix"),
				graph->adjacency_matrix (), *graph);
	md.ShowModal ();
}
