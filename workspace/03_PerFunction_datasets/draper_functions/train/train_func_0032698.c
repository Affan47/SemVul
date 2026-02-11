rec_save_vlists(graph_t * g)
{
    int c;

    save_vlist(g);
    for (c = 1; c <= GD_n_cluster(g); c++)
	rec_save_vlists(GD_clust(g)[c]);
}
