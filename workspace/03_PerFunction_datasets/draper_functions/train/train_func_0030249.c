ctpl_value_array_index (const CtplValue *value,
                        gsize            idx)
{
  gsize   i;
  GSList *tmp;

  g_return_val_if_fail (CTPL_VALUE_HOLDS_ARRAY (value), NULL);

  for (i = 0, tmp = value->value.v_array; i < idx && tmp; i++) {
    tmp = tmp->next;
  }

  return tmp ? tmp->data : NULL;
}
