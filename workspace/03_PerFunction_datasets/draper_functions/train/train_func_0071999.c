atk_relation_new (AtkObject       **targets,
                  gint            n_targets,
                  AtkRelationType relationship)
{
  AtkRelation *relation;
  int         i;
  GValueArray *array;
  GValue      *value;

  g_return_val_if_fail (targets != NULL, NULL);

  array = g_value_array_new (n_targets);
  for (i = 0; i < n_targets; i++)
  {
    value = g_new0 (GValue, 1);
    g_value_init (value, ATK_TYPE_OBJECT);
    g_value_set_object (value, targets[i]);
    array = g_value_array_append (array, value);
    g_value_unset (value);
    g_free (value);
  }

  relation =  g_object_new (ATK_TYPE_RELATION,
                            "relation_type", relationship,
                            "target", array,
                            NULL);

  g_value_array_free (array);

  return relation;
}
