make_uniting_coercion (NODE_T * n, MOID_T * q)
{
  make_coercion (n, UNITING, derow (q));
  if (IS (q, ROW_SYMBOL) || IS (q, FLEX_SYMBOL)) {
    make_rowing_coercion (n, derow (q), q);
  }
}
