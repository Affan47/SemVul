ho_bitmap_filter_count_objects (const ho_bitmap * m)
{
  ho_objmap *o_obj;
  int count;

  o_obj = ho_objmap_new_from_bitmap (m);
  if (!o_obj)
    return -1;

  count = ho_objmap_get_size (o_obj);
  ho_objmap_free (o_obj);

  return count;
}
