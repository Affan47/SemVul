gimplify_pure_cond_expr (tree *expr_p, gimple_seq *pre_p)
{
  tree expr = *expr_p, cond;
  enum gimplify_status ret, tret;
  enum tree_code code;

  cond = gimple_boolify (COND_EXPR_COND (expr));


  code = TREE_CODE (cond);
  if (code == TRUTH_ANDIF_EXPR)
    TREE_SET_CODE (cond, TRUTH_AND_EXPR);
  else if (code == TRUTH_ORIF_EXPR)
    TREE_SET_CODE (cond, TRUTH_OR_EXPR);
  ret = gimplify_expr (&cond, pre_p, NULL, is_gimple_condexpr, fb_rvalue);
  COND_EXPR_COND (*expr_p) = cond;

  tret = gimplify_expr (&COND_EXPR_THEN (expr), pre_p, NULL,
				   is_gimple_val, fb_rvalue);
  ret = MIN (ret, tret);
  tret = gimplify_expr (&COND_EXPR_ELSE (expr), pre_p, NULL,
				   is_gimple_val, fb_rvalue);

  return MIN (ret, tret);
}
