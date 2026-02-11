zmat_connect_sort(GSList *molecule)
{
GSList *list, *path, *sorted;
struct core_pak *core, *next;


for (list=molecule ; list ; list=g_slist_next(list))
  {
  core = list->data;
  core->status &= ~PRUNED;
  }


next = NULL;
path = NULL;
for (list=molecule ; list ; list=g_slist_next(list))
  {
  core = list->data;

  if (g_slist_length(core->bonds) == 1)
    {
    next = core;
    break;
    }
  }


if (next)
  path = g_slist_append(path, core);
else
  path = g_slist_append(path, molecule->data);


sorted = NULL;
while (path)
  {
  core = path->data;

  if (!(core->status & PRUNED))
    {
    core->status |= PRUNED;
    sorted = g_slist_append(sorted, core);
    }

  while (core)
    {
    next = zmat_connect_next(core);

    if (next)
      {
      if (g_slist_length(next->bonds) > 2)
        path = g_slist_append(path, next);

      next->status |= PRUNED;
      sorted = g_slist_append(sorted, next);
      }

    core = next;
    }


   while (path)
     {
     core = zmat_connect_next(path->data);
     if (core)
       break;

     path = g_slist_next(path);
     }
  }

return(sorted);
}
