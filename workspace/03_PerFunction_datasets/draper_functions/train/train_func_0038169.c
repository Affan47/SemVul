disp_ptree(PATNODE *node, int level)
{
  int i;

  for (i=0;i<level;i++) {
    printf("-");
  }
  if (node->left0 == NULL && node->right1 == NULL) {
    printf("LEAF:%d\n", node->value.data);
  } else {
    printf("%d\n", node->value.thres_bit);
    if (node->left0 != NULL) {
      disp_ptree(node->left0, level+1);
    }
    if (node->right1 != NULL) {
      disp_ptree(node->right1, level+1);
    }
  }
}
