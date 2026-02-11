getLabelTree (LabelDsymbol *label)
{
  if (!label->statement)
    return NULL_TREE;

  if (!label->statement->lblock)
    {
      tree label_decl = d_build_label (label->statement->loc, label->ident);
      TREE_USED (label_decl) = 1;
      label->statement->lblock = label_decl;
    }
  return label->statement->lblock;
}
