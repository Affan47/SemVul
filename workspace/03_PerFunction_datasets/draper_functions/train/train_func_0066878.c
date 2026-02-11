model_allocate (int model_w, int model_h)
{
  CriticalModel		*mm;

  mm = malloc (sizeof (CriticalModel));
  if (!mm)
    return 0;

  mm->width = model_w;
  mm->height = model_h;

  mm->cells = malloc (sizeof (unsigned short) * model_w * model_h);
  if (!mm->cells)
    return 0;

  return mm;
}
