free_EXPR_LIST_list (rtx *listp)
{
  if (*listp == 0)
    return;
  free_list (listp, &unused_expr_list);
}
