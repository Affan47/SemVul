cxx_type_promotes_to (tree type)
{
  tree promote;


  type = type_decays_to (type);

  promote = type_promotes_to (type);
  if (same_type_p (type, promote))
    promote = type;

  return promote;
}
