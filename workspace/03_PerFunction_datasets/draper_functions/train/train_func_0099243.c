get_display_data (Display *display,
                  Bool     create)
{
  ListNode *node;
  AgPerDisplayData *dd;

  node = display_datas;
  while (node != NULL)
    {
      dd = (AgPerDisplayData*) node;

      if (dd->display == display)
        return dd;

      node = node->next;
    }

  if (!create)
    return NULL;

  dd = Xcalloc (1, sizeof (AgPerDisplayData));
  if (dd == NULL)
    return NULL;

  dd->display = display;
  dd->async.next = display->async_handlers;
  dd->async.handler = async_get_property_handler;
  dd->async.data = (XPointer) dd;
  dd->display->async_handlers = &dd->async;

  append_to_list (&display_datas,
                  &display_datas_tail,
                  &dd->node);

  return dd;
}
