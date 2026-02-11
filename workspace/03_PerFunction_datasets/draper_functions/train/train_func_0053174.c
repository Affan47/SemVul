Map(register Node *node) {
  register guint id;


  if (node->children != 0)
    for (id=0; id < 8; id++)
      if (node->children & (1 << id))
        Map(node->child[id]);
  if (node->number_unique > 0) {

      cube.colormap[cube.colors].red=(unsigned char)
        ((node->total_red+(node->number_unique >> 1))/node->number_unique);
      cube.colormap[cube.colors].green=(unsigned char)
        ((node->total_green+(node->number_unique >> 1))/node->number_unique);
      cube.colormap[cube.colors].blue=(unsigned char)
        ((node->total_blue+(node->number_unique >> 1))/node->number_unique);
      node->color_number=cube.colors++;
  }
}
