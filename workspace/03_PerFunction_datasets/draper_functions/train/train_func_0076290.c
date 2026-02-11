reset_status_vars()
{
  SHOW_VAR *ptr= (SHOW_VAR*) all_status_vars.buffer;
  SHOW_VAR *last= ptr + all_status_vars.elements;
  for (; ptr < last; ptr++)
  {

    if (ptr->type == SHOW_LONG)
      *(ulong*) ptr->value= 0;
  }
}
