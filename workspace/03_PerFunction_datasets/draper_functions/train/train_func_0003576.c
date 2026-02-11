ecs_maillage__ret_taille(const ecs_maillage_t  *maillage)
{
  size_t       taille;
  ecs_int_t    ient;


  assert(maillage != NULL);

  taille = sizeof(*maillage);

  for (ient = 0; ient < ECS_N_ENTMAIL; ient++) {

    if (maillage->table_def[ient] != NULL)
      taille += ecs_table__ret_taille(maillage->table_def[ient]);

    if (maillage->table_att[ient] != NULL)
      taille += ecs_table__ret_taille(maillage->table_att[ient]);

    if (maillage->elt_fam[ient] != NULL)
      taille += (  ecs_table__ret_elt_nbr(maillage->table_def[ient])
                 * sizeof(int));

    if (maillage->n_connect_couples[ient] != 0)
      taille += maillage->n_connect_couples[ient] * sizeof(ecs_int_t);

    if (maillage->famille[ient] != NULL)
      taille += ecs_famille_chaine__ret_taille(maillage->famille[ient]);
  }

  return (float)taille;
}
