lineeditor_history_remove
   ___P((___device_tty *self,
         lineeditor_history *item),
        (self,
         item)
___device_tty *self;
lineeditor_history *item;)
{
  ___device_tty *d = self;

  lineeditor_history *prev = item->prev;
  lineeditor_history *next = item->next;

  if (prev == item)
    d->hist_last = NULL;
  else
    {
      next->prev = prev;
      prev->next = next;
      item->prev = item;
      item->next = item;
      if (d->hist_last == item)
        d->hist_last = prev;
    }
}
