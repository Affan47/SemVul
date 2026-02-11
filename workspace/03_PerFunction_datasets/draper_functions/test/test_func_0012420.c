is_model_duplicate (Babl *babl, int components, BablComponent **component)
{
  int   i;

  if (babl->model.components != components)
    return 0;

  for (i = 0; i < components; i++)
    {
      if (babl->model.component[i] != component[i])
        return 0;
    }

  return 1;
}
