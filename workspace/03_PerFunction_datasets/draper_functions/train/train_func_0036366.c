FcConfigAllocExpr (FcConfig *config)
{
  if (!config->expr_pool || config->expr_pool->next == config->expr_pool->end)
  {
    FcExprPage *new_page;

    new_page = malloc (sizeof (FcExprPage));
    if (!new_page)
      return 0;

    new_page->next_page = config->expr_pool;
    new_page->next = new_page->exprs;
    config->expr_pool = new_page;
  }

  return config->expr_pool->next++;
}
