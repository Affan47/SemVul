ParseColorset(char *arg1, char *arg2, void *offset_deskinfo,
			  void *offset_item, int *colorset_global)
{
  Bool all_desks = False;
  int colorset = 0;
  int i;
  int desk;
  unsigned long colorset_offset = (unsigned long)offset_deskinfo;
  unsigned long item_colorset_offset = (unsigned long)offset_item;

  sscanf(arg2, "%d", &colorset);
  AllocColorset(colorset);
  if (StrEquals(arg1, "*"))
  {
    all_desks = True;
    desk = Scr.CurrentDesk;
  }
  else
  {
    desk = desk1;
    sscanf(arg1,"%d",&desk);
  }
  if (fAlwaysCurrentDesk)
  {
    if (all_desks)
    {
      *colorset_global = colorset;
    }
    else
    {
      PagerStringList *item;

      item = FindDeskStrings(desk);
      if (item->next != NULL)
      {
	*(int *)(((char *)(item->next)) + item_colorset_offset) = colorset;
      }
      else
      {

	item = NewPagerStringItem(item, desk);
	*(int *)(((char *)item) + item_colorset_offset) = colorset;
      }
    }
    if (desk == Scr.CurrentDesk || all_desks)
    {
      *(int *)(((char *)&Desks[0]) + colorset_offset) = colorset;
    }
  }
  else if (all_desks)
  {
    for (i = 0; i < ndesks; i++)
    {
      *(int *)(((char *)&Desks[i]) + colorset_offset) = colorset;
    }
  }
  else if((desk >= desk1)&&(desk <=desk2))
  {
    *(int *)(((char *)&Desks[desk - desk1]) + colorset_offset) = colorset;
  }

  return;
}
