comparisonForHavingIndices(gconstpointer a, gconstpointer b,
				       gpointer user_data)
{
  float c;
  float *array;

  array = (float*)user_data;

  c = array[*(int*)b] - array[*(int*)a];

  if (c < 0.f)
    return  (gint)(1);
  else if (c > 0.f)
    return (gint)(-1);
  else
    return (gint)(0);
}
