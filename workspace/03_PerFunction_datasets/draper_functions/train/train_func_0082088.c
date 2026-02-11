report_type(const Token *t)
#else
report_type(t)
     Token *t;
#endif
{
  msg_tail(sized_typename((int)datatype_of(t->TOK_type),t->size));
  if(is_true(ID_EXPR,t->TOK_flags))
    msg_tail(hashtab[t->value.integer].name);
  else if(is_true(LIT_CONST,t->TOK_flags)) {
    msg_tail("const");
    msg_expr_tree(t);
  }
  else {
    msg_tail("expr");
    msg_expr_tree(t);
  }
}
