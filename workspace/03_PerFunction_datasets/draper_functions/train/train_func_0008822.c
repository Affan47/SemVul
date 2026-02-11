tbbt_end(TBBT_NODE * root, intn side)
{
    if (root == NULL)
        return (NULL);
    while (HasChild(root, side))
      {
          root = root->link[side];
      }
    return (root);
}
