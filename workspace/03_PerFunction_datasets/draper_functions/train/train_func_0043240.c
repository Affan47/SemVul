maybe_free_display_data (AgPerDisplayData *dd)
{
  if (dd->pending_tasks == NULL &&
      dd->completed_tasks == NULL)
    {
      DeqAsyncHandler (dd->display, &dd->async);
      remove_from_list (&display_datas, &display_datas_tail,
                        &dd->node);
      XFree (dd);
    }
}
