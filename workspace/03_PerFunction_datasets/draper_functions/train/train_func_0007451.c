Node_fwrite (FILE *fp, Node_T node) {
  int leftindex, rightindex;

  if (node != NULL) {
    if (node->left == NULL) {
      leftindex = -1;
    } else {
      leftindex = node->left->index;
    }

    if (node->right == NULL) {
      rightindex = -1;
    } else {
      rightindex = node->right->index;
    }

    debug(printf("Writing node %u %d %d\n",node->value,node->a,node->b));
    FWRITE_UINT(node->value,fp);
    FWRITE_INT(node->a,fp);
    FWRITE_INT(node->b,fp);
    FWRITE_INT(leftindex,fp);
    FWRITE_INT(rightindex,fp);

    Node_fwrite(fp,node->left);
    Node_fwrite(fp,node->right);
  }
  return;
}
