create_outline_filter (int radius)
{
  ConvFilter *filter;
  double *iter;

  filter = g_new0 (ConvFilter, 1);
  filter->size = radius * 2 + 1;
  filter->data = g_new (double, filter->size * filter->size);

  for (iter = filter->data;
       iter < filter->data + (filter->size * filter->size);
       iter++)
    {
      *iter = 1.0;
    }

  return filter;
}
