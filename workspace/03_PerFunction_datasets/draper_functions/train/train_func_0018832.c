append_entry (struct entry **entp, struct entry *ent)
{


  struct entry *e;


  for (e = *entp; e && e->next; e = e->next)
    ;

  if (e)
    e->next = ent;
  else
    *entp = ent;
}
