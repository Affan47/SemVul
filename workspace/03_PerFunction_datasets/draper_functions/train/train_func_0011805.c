schedule_destruct_event_48h(struct Channel* chptr)
{
  struct DestructEvent* new_event;


  if (chptr->destruct_event)
    return;


  new_event = (struct DestructEvent*)MyMalloc(sizeof(struct DestructEvent));
  new_event->expires = TStime() + 172800;
  new_event->next_event = NULL;
  new_event->prev_event = days_list_top;
  new_event->chptr = chptr;

  if (days_list_top)
    days_list_top->next_event = new_event;
  days_list_top = new_event;
  if (!days_list_bottom)
    days_list_bottom = new_event;

  chptr->destruct_event = new_event;
}
