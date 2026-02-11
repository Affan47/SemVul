write_binary_value_expr(std::ostream& out, const value_expr_t * expr)
{
  if (! expr) {
    write_binary_bool(out, false);
    return;
  }
  write_binary_bool(out, true);
  write_binary_number(out, expr->kind);

  if (expr->kind > value_expr_t::TERMINALS)
    write_binary_value_expr(out, expr->left);

  switch (expr->kind) {
  case value_expr_t::O_ARG:
  case value_expr_t::INDEX:
    write_binary_long(out, expr->arg_index);
    break;
  case value_expr_t::CONSTANT:
    write_binary_value(out, *expr->value);
    break;

  case value_expr_t::F_CODE_MASK:
  case value_expr_t::F_PAYEE_MASK:
  case value_expr_t::F_NOTE_MASK:
  case value_expr_t::F_ACCOUNT_MASK:
  case value_expr_t::F_SHORT_ACCOUNT_MASK:
  case value_expr_t::F_COMMODITY_MASK:
    if (expr->mask) {
      write_binary_bool(out, true);
      write_binary_mask(out, expr->mask);
    } else {
      write_binary_bool(out, false);
    }
    break;

  default:
    if (expr->kind > value_expr_t::TERMINALS)
      write_binary_value_expr(out, expr->right);
    break;
  }

}
