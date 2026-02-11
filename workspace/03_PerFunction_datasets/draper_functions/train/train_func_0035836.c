tenm_image_delete(tenm_image *p)
{
  int i;

  if (p == NULL)
  {
    fprintf(stderr, "tenm_image_delete: p is NULL\n");
    return;
  }
  if (p->n <= 0)
  {
    fprintf(stderr, "tenm_image_delete: p->n is non-positive (%d)\n", p->n);
    return;
  }
  if (p->image == NULL)
  {
    fprintf(stderr, "tenm_image_delete: p->image is NULL\n");
    return;
  }

  for (i = 0; i < p->n; i++)
    SDL_FreeSurface(p->image[i]);
  free(p->image);
  free(p);
}
