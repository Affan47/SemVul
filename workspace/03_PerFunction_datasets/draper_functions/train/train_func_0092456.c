pgs_presentation_segment_find_object (PgsPresentationSegment * ps,
    guint16 obj_id)
{
  guint i;
  if (ps->objects == NULL)
    return NULL;

  for (i = 0; i < ps->objects->len; i++) {
    PgsCompositionObject *cur =
        &g_array_index (ps->objects, PgsCompositionObject, i);
    if (cur->id == obj_id)
      return cur;
  }

  return NULL;
}
