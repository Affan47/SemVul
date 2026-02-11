fs_vector_find (FishSoundVector * vector, const void * data)
{
  void * v_data;
  int i;

  for (i = 0; i < vector->nr_elements; i++) {
    v_data = vector->data[i];
    if (vector->cmp (v_data, data))
      return v_data;
  }

  return NULL;
}
