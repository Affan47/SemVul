contains (const Clparam &p) const
{
  list<Clparam>::const_iterator iter;
  unsigned int i;

  for (iter = _params.begin (); iter != _params.end (); iter++)
    {
      if (!iter->get_long_only () && (iter->get_short_rep (0) != 0))
        for (i = 0; i < p.get_num_short_reps (); i++)
          if (iter->contains (p.get_short_rep (i)))
            return true;

      if ((iter->get_long_rep ().length () > 0) && (iter->get_long_rep () == p.get_long_rep ()))
        return true;
    }
  return false;
}
