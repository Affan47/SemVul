set_explicit_duration_for_all_locks()
{
  int i;
  MDL_ticket *ticket;


  m_tickets[MDL_EXPLICIT].swap(m_tickets[MDL_TRANSACTION]);

  for (i= 0; i < MDL_EXPLICIT; i++)
  {
    Ticket_iterator it_ticket(m_tickets[i]);

    while ((ticket= it_ticket++))
    {
      m_tickets[i].remove(ticket);
      m_tickets[MDL_EXPLICIT].push_front(ticket);
    }
  }

#ifndef DBUG_OFF
  Ticket_iterator exp_it(m_tickets[MDL_EXPLICIT]);

  while ((ticket= exp_it++))
    ticket->m_duration= MDL_EXPLICIT;
#endif
}
