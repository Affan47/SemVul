inf_adopted_algorithm_is_reachable(InfAdoptedAlgorithm* algorithm,
                                   InfAdoptedStateVector* v)
{
  InfAdoptedAlgorithmPrivate* priv;
  InfAdoptedUser** user;

  priv = INF_ADOPTED_ALGORITHM_PRIVATE(algorithm);

  g_assert(
    inf_adopted_state_vector_causally_before(v, priv->current) == TRUE
  );

  for(user = priv->users_begin; user != priv->users_end; ++ user)
    if(!inf_adopted_algorithm_is_component_reachable(algorithm, v, *user))
      return FALSE;

  return TRUE;
}
