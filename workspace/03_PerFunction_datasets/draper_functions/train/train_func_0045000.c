dialog_exists(gint type, struct model_pak *model)
{
GSList *list;
struct dialog_pak *dialog;

for (list=sysenv.dialog_list ; list ; list=g_slist_next(list))
  {
  dialog = list->data;

  if (model)
    {
    if (dialog->model == model && dialog->type == type)
      return(TRUE);
    }
  else
    {
    if (dialog->type == type)
      return(TRUE);
    }
  }
return(FALSE);
}
