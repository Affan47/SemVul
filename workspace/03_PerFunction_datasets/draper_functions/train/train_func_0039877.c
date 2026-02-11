pos_clusters(graph_t * g)
{
    if (GD_n_cluster(g) > 0) {
	contain_clustnodes(g);
	keepout_othernodes(g);
	contain_subclust(g);
	separate_subclust(g);
    }
}
