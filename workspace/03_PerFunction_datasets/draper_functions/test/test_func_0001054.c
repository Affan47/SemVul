Print(R3MeshSearchTreeNode *node, int depth) const
{

  if (!node) return 0;


  int ndecendents0 = 0;
  int ndecendents1 = 0;


  if (node->children[0] && node->children[1]) {

    ndecendents0 = Print(node->children[0], depth+1);
    ndecendents1 = Print(node->children[1], depth+1);


    printf("%d", depth);
    for (int i = 0; i <= depth; i++) printf("  ");
    printf("I %d : %d %d %g\n", node->big_faces.NEntries(), ndecendents0, ndecendents1, (double) ndecendents0 / (double) ndecendents1);
  }
  else {
    printf("%d", depth);
    for (int i = 0; i <= depth; i++) printf("  ");
    printf("L %d \n", node->small_faces.NEntries());
  }


  return 1 + ndecendents0 + ndecendents1;
}
