dfs (Vertex *v, wxString &s)
{
	Graph::v_iterator vit;


	for (vit = v_begin (); vit != v_end (); ++vit)
		(*vit)->mark = 0;

	dfs_do (v, s, 1);
}
