strip_pointer_operator (tree t)
{
  while (POINTER_TYPE_P (t))
    t = TREE_TYPE (t);
  return t;
}
