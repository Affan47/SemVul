inorder (AtkObject * collection, MatchRulePrivate * mrp,
         GList * ls, gint kount, gint max,
         AtkObject * obj,
         gboolean flag, AtkObject * pobj, dbus_bool_t traverse)
{
  int i = 0;


  kount = sort_order_canonical (mrp, ls, kount, max, obj, 0, TRUE,
                                NULL, TRUE, TRUE);


  while ((max == 0 || kount < max) && obj != collection)
    {
      AtkObject *parent = atk_object_get_parent (obj);
      i = atk_object_get_index_in_parent (obj);
      kount = sort_order_canonical (mrp, ls, kount, max, parent,
                                    i + 1, TRUE, FALSE, TRUE, TRUE);
      obj = parent;
    }

  if (max == 0 || kount < max)
    {
      kount = sort_order_canonical (mrp, ls, kount, max,
                                    obj, i + 1, TRUE, FALSE, TRUE, TRUE);
    }

  return kount;
}
