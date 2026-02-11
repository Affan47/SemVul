length_get_value (gpointer test, GValue * value)
{
  LengthTest *t = test;

  g_value_set_int64 (value, t ? t->value : -1);
}
