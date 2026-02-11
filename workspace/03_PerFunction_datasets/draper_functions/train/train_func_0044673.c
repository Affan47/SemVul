gimplify_one_sizepos (tree *expr_p, gimple_seq *stmt_p)
{
  tree expr = *expr_p;


  if (is_gimple_sizepos (expr))
    return;

  *expr_p = unshare_expr (expr);

  gimplify_expr (expr_p, stmt_p, NULL, is_gimple_val, fb_rvalue);
}
