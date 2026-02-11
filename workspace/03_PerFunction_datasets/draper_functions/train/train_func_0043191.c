clear_opname_map (opname_map *m)
{
  opname_map_e *e;

  while (m->head != NULL)
    {
      e = m->head;
      m->head = e->next;
      free (e);
    }
  m->tail = &m->head;
}
