set_layers(struct reqtree *tree)
{
  int i;
  int num_layers = 0;


  for (i = 0; i < tree->num_nodes; i++) {
    num_layers = MAX(num_layers, tree->nodes[i]->layer);
  }
  num_layers++;
  tree->num_layers = num_layers;

  {

    int T[num_layers];

    tree->layers = fc_malloc(sizeof(*tree->layers) * num_layers);
    tree->layer_size = fc_malloc(sizeof(*tree->layer_size) * num_layers);
    for (i = 0; i < num_layers; i++) {
      T[i] = 0;
      tree->layer_size[i] = 0;
    }
    for (i = 0; i < tree->num_nodes; i++) {
      tree->layer_size[tree->nodes[i]->layer]++;
    }

    for (i = 0; i < num_layers; i++) {
      tree->layers[i] =
	  fc_malloc(sizeof(*tree->layers[i]) * tree->layer_size[i]);
    }
    for (i = 0; i < tree->num_nodes; i++) {
      struct tree_node *node = tree->nodes[i];

      tree->layers[node->layer][T[node->layer]] = node;
      node->order = T[node->layer];
      T[node->layer]++;
    }
  }
}
