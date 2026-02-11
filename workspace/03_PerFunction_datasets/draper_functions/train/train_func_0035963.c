lash_event_destroy(lash_event_t * event_ptr)
{
  free(event_ptr->string);
  if (event_ptr == &g_event)
  {
    event_ptr->type = 0;
    event_ptr->string = NULL;
  }
  else
  {
    free(event_ptr);
  }
}
