s48_free_subcall (s48_call_t subcall)
{
  s48_call_t parent = subcall->subcall_parent;
  if (subcall->next_subcall == subcall) {
    parent->child = NULL;
  } else {
    parent->child = subcall->next_subcall;
    subcall->prev_subcall->next_subcall = subcall->next_subcall;
    subcall->next_subcall->prev_subcall = subcall->prev_subcall;
  }
  free_call (subcall);
}
