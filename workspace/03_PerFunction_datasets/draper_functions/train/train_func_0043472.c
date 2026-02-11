metafile_collect_times (MetaFile *file,
			gint64 *time_t_min,
			gint64 *time_t_max)
{
  GList *l;
  MetaFile *child;

  if (*time_t_min == 0)
    *time_t_min = file->last_changed;
  else if (file->last_changed != 0 && file->last_changed < *time_t_min)
    *time_t_min = file->last_changed;

  if (file->last_changed > *time_t_max)
    *time_t_max = file->last_changed;

  for (l = file->children; l != NULL; l = l->next)
    {
      child = l->data;
      metafile_collect_times (child, time_t_min, time_t_max);
    }
}
