fini_object_sizes (void)
{
  int object_size_type;

  for (object_size_type = 0; object_size_type <= 3; object_size_type++)
    {
      free (object_sizes[object_size_type]);
      BITMAP_FREE (computed[object_size_type]);
      object_sizes[object_size_type] = NULL;
    }
}
