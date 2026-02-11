bg_accelerator_map_remove(bg_accelerator_map_t * m, int id)
  {
  int index;
  index = find_by_id(m, id);
  if(index < 0)
    return;
  if(index < m->num - 1)
    {
    memmove(m->accels + index,
            m->accels + index + 1,
            sizeof(*m->accels) * (m->num - 1 - index));
    }
  m->num--;
  }
