constraint_vec_find (vec<constraint_t> vec,
		     struct constraint lookfor)
{
  unsigned int place;
  constraint_t found;

  if (!vec.exists ())
    return NULL;

  place = vec.lower_bound (&lookfor, constraint_less);
  if (place >= vec.length ())
    return NULL;
  found = vec[place];
  if (!constraint_equal (*found, lookfor))
    return NULL;
  return found;
}
