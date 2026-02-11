fetch_conversion(TreeNode *x, int create, ExtensionType type)
{
  Extension *y;
  y = create ? obtain_extension(x, type) : lookup_extension (x, type);
  if (y) {
    return &(y->data);
  } else {
    return NULL;
  }

}
