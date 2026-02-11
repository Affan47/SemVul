entry() const
  {
    if (0 == m->status)
      return Entry();

    return Entry(m->status->entry);
  }
