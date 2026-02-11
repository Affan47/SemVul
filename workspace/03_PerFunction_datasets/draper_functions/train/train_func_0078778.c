atk_relation_remove_target (AtkRelation *relation,
                            AtkObject *target)
{
  gboolean ret = FALSE;
  GPtrArray *array;

  array = atk_relation_get_target (relation);

  if (array && g_ptr_array_remove (array, target))
    {
      g_object_weak_unref (G_OBJECT (target),
                           (GWeakNotify) delete_object_while_in_relation,
                           relation->target);
      ret = TRUE;
    }
  return ret;
}
