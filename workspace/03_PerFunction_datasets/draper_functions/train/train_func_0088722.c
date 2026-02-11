copy_element (struct format_arg *newelement,
              const struct format_arg *oldelement)
{
  newelement->repcount = oldelement->repcount;
  newelement->presence = oldelement->presence;
  newelement->type = oldelement->type;
  if (oldelement->type == FAT_LIST)
    newelement->list = copy_list (oldelement->list);
}
