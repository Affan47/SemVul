atk_relation_set_remove (AtkRelationSet *set,
                         AtkRelation    *relation)
{
  GPtrArray *array_item;
  AtkRelationType relationship;

  g_return_if_fail (ATK_IS_RELATION_SET (set));

  array_item = set->relations;
  if (array_item == NULL)
    return;

  if (g_ptr_array_remove (array_item, relation))
  {
    g_object_unref (relation);
  }
  else
  {
    relationship = atk_relation_get_relation_type (relation);
    if (atk_relation_set_contains (set, relationship))
    {
      AtkRelation *exist_relation;
      gint i;
      exist_relation = atk_relation_set_get_relation_by_type (set, relationship);
      for (i = 0; i < relation->target->len; i++)
      {
        AtkObject *target = g_ptr_array_index(relation->target, i);
        atk_relation_remove_target (exist_relation, target);
      }
    }
  }
}
