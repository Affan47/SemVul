atk_object_remove_relationship (AtkObject       *object,
                                AtkRelationType relationship,
                                AtkObject       *target)
{
  gboolean ret = FALSE;
  AtkRelation *relation;
  GPtrArray *array;

  g_return_val_if_fail (ATK_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (ATK_IS_OBJECT (target), FALSE);

  relation = atk_relation_set_get_relation_by_type (object->relation_set, relationship);

  if (relation)
    {
      ret = atk_relation_remove_target (relation, target);
      array = atk_relation_get_target (relation);
      if (!array || array->len == 0)
        atk_relation_set_remove (object->relation_set, relation);
    }
  return ret;
}
