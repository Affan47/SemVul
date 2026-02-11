print_lattice_node(struct lattice_info *info, struct lattice_node *node)
{
  if (!node) {
    printf("**lattice_node (null)*\n");
    return ;
  }
  printf("**lattice_node probability=%.128f\n", node->real_probability);
  if (node->mw) {
    anthy_print_metaword(info->sc, node->mw);
  }
}
