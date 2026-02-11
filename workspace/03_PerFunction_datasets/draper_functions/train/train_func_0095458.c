meta_draw_op_list_append (MetaDrawOpList       *op_list,
                          MetaDrawOp           *op)
{
  if (op_list->n_ops == op_list->n_allocated)
    {
      op_list->n_allocated *= 2;
      op_list->ops = g_renew (MetaDrawOp*, op_list->ops, op_list->n_allocated);
    }

  op_list->ops[op_list->n_ops] = op;
  op_list->n_ops += 1;
}
