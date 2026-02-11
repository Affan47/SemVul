unit_dequeue(void)
{
  int lit;

  if (Unit_queue_last < Unit_queue_first)
    return(0);
  else {
    lit = Unit_queue[Unit_queue_first];
    Unit_queue_first++;
    Atoms[abs(lit)].enqueued_value = NOT_DETERMINED;
#ifdef TRACE
    printf("		dequeue: ");
    p_unit(lit);
    printf(" (%d).\n", lit);
#endif
    return(lit);
  }
}
