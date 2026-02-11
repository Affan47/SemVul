opj_tgt_init(opj_tgt_tree_t * p_tree,OPJ_UINT32 p_num_leafs_h, OPJ_UINT32 p_num_leafs_v)
{
        OPJ_INT32 l_nplh[32];
        OPJ_INT32 l_nplv[32];
        opj_tgt_node_t *l_node = 00;
        opj_tgt_node_t *l_parent_node = 00;
        opj_tgt_node_t *l_parent_node0 = 00;
        OPJ_UINT32 i;
        OPJ_INT32 j,k;
        OPJ_UINT32 l_num_levels;
        OPJ_UINT32 n;
        OPJ_UINT32 l_node_size;

        if (! p_tree){
                return 00;
        }

        if ((p_tree->numleafsh != p_num_leafs_h) || (p_tree->numleafsv != p_num_leafs_v)) {
                p_tree->numleafsh = p_num_leafs_h;
                p_tree->numleafsv = p_num_leafs_v;

                l_num_levels = 0;
                l_nplh[0] = p_num_leafs_h;
                l_nplv[0] = p_num_leafs_v;
                p_tree->numnodes = 0;
                do
                {
                        n = l_nplh[l_num_levels] * l_nplv[l_num_levels];
                        l_nplh[l_num_levels + 1] = (l_nplh[l_num_levels] + 1) / 2;
                        l_nplv[l_num_levels + 1] = (l_nplv[l_num_levels] + 1) / 2;
                        p_tree->numnodes += n;
                        ++l_num_levels;
                }
                while (n > 1);


                if (p_tree->numnodes == 0) {
                        opj_tgt_destroy(p_tree);
                        return 00;
                }
                l_node_size = p_tree->numnodes * sizeof(opj_tgt_node_t);

                if (l_node_size > p_tree->nodes_size) {
                        opj_tgt_node_t* new_nodes = (opj_tgt_node_t*) opj_realloc(p_tree->nodes, l_node_size);
                        if (! new_nodes) {
                                fprintf(stderr, "ERROR Not enough memory to reinitialize the tag tree\n");
                                opj_tgt_destroy(p_tree);
                                return 00;
                        }
                        p_tree->nodes = new_nodes;
                        memset(((char *) p_tree->nodes) + p_tree->nodes_size, 0 , l_node_size - p_tree->nodes_size);
                        p_tree->nodes_size = l_node_size;
                }
                l_node = p_tree->nodes;
                l_parent_node = &p_tree->nodes[p_tree->numleafsh * p_tree->numleafsv];
                l_parent_node0 = l_parent_node;

                for (i = 0; i < l_num_levels - 1; ++i) {
                        for (j = 0; j < l_nplv[i]; ++j) {
                                k = l_nplh[i];
                                while (--k >= 0) {
                                        l_node->parent = l_parent_node;
                                        ++l_node;
                                        if (--k >= 0) {
                                                l_node->parent = l_parent_node;
                                                ++l_node;
                                        }
                                        ++l_parent_node;
                                        }
                                if ((j & 1) || j == l_nplv[i] - 1)
                                {
                                        l_parent_node0 = l_parent_node;
                                }
                                else
                                {
                                        l_parent_node = l_parent_node0;
                                        l_parent_node0 += l_nplh[i];
                                }
                        }
                }
                l_node->parent = 0;
        }
        opj_tgt_reset(p_tree);

        return p_tree;
}
