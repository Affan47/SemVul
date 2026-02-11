uct_find_node(struct uct_tree *tree, struct uct_node *parent, int move)
{
  struct uct_node *node = NULL;
  Hash_data *boardhash = &tree->game.mc.hash;
  unsigned int hash_index = hashdata_remainder(*boardhash,
					       tree->hashtable_size);
  unsigned int *hashtable = tree->hashtable_even;
  if (tree->game.depth & 1)
    hashtable = tree->hashtable_odd;

  while (hashtable[hash_index] != 0) {
    int node_index = hashtable[hash_index];
    gg_assert(node_index > 0 && node_index < tree->num_nodes);
    if (hashdata_is_equal(tree->nodes[node_index].boardhash, *boardhash)) {
      node = &tree->nodes[node_index];
      break;
    }
    hash_index++;
    if (hash_index >= tree->hashtable_size)
      hash_index = 0;
  }

  if (!node) {
    node = uct_init_node(tree, NULL);
    gg_assert(hash_index < tree->hashtable_size);
    hashtable[hash_index] = node - tree->nodes;
  }


  if (parent) {
    struct uct_arc *arc = &tree->arcs[tree->num_used_arcs++];
    gg_assert(tree->num_used_arcs < tree->num_arcs);
    arc->move = move;
    arc->node = node;
    if (parent->child)
      arc->next = parent->child;
    else
      arc->next = NULL;
    parent->child = arc;
  }

  return node;
}
