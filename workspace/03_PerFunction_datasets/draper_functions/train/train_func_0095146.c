expand_decl (tree decl)
{

  if (DECL_INITIAL (decl))
    {
      tree exp = build_vinit (decl, DECL_INITIAL (decl));
      current_irstate->addExp (exp);
      DECL_INITIAL (decl) = NULL_TREE;
    }
}
