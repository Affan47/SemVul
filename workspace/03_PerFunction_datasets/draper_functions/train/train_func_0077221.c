DestroyColorInfo(void)
{
  ColorInfo
    *color_info;

  register ColorInfo
    *p;

  for (p=color_list; p != (const ColorInfo *) NULL; )
  {
    color_info=p;
    p=p->next;
    DestroyColorInfoEntry(color_info);
  }
  color_list=(ColorInfo *) NULL;
  DestroySemaphoreInfo(&color_semaphore);
}
