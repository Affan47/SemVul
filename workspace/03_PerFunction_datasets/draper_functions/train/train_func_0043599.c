ctpl_value_set_array_internal (CtplValue     *value,
                               const GSList  *values)
{
  GSList *new_values = NULL;

  for (; values != NULL; values = values->next) {
    new_values = g_slist_prepend (new_values, ctpl_value_dup (values->data));
  }
  new_values = g_slist_reverse (new_values);
  ctpl_value_free_value (value);
  value->type = CTPL_VTYPE_ARRAY;
  value->value.v_array = new_values;
}
