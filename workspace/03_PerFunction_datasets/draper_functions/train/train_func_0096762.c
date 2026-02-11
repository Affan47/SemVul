_clutter_meta_group_get_meta (ClutterMetaGroup *group,
                              const gchar      *name)
{
  GList *l;

  for (l = group->meta; l != NULL; l = l->next)
    {
      ClutterActorMeta *meta = l->data;

      if (g_strcmp0 (meta->priv->name, name) == 0)
        return meta;
    }

  return NULL;
}
