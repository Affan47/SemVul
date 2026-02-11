delete_graph(glp_graph *G)
{     dmp_delete_pool(G->pool);
      xfree(G->v);
      if (G->index != NULL) avl_delete_tree(G->index);
      return;
}
