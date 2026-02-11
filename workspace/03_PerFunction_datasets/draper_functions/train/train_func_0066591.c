ecs_maillage__connect_descend(ecs_maillage_t * maillage)
{
  size_t         nbr_elt_new;
  ecs_tab_int_t  vect_transf;
  ecs_tab_int_t  signe_elt;

  ecs_size_t nbr_fac_old = 0;


  assert(maillage != NULL);
  assert(maillage->typ_connect == ECS_MAILLAGE_CONNECT_NODALE);

  maillage->typ_connect = ECS_MAILLAGE_CONNECT_DESCENDANTE;

  if (maillage->table_def[ECS_ENTMAIL_CEL] == NULL)
    return;


  if (maillage->table_def[ECS_ENTMAIL_FAC] != NULL)
    nbr_fac_old = ecs_table__ret_elt_nbr(maillage->table_def[ECS_ENTMAIL_FAC]);

  ecs_table_def__decompose_cel(&maillage->table_def[ECS_ENTMAIL_FAC],
                               maillage->table_def[ECS_ENTMAIL_CEL]);

  assert(maillage->table_att[ECS_ENTMAIL_FAC] == NULL);


  ecs_table_def__nettoie_som_fac(&(maillage->n_vertices),
                                 &(maillage->vertex_coords),
                                 maillage->table_def[ECS_ENTMAIL_FAC]);


  nbr_elt_new = 0;

  signe_elt.nbr = 0;
  signe_elt.val = NULL;

  vect_transf = ecs_table_def__fusionne(maillage->table_def[ECS_ENTMAIL_FAC],
                                        &nbr_elt_new,
                                        &signe_elt);


  assert(maillage->table_att[ECS_ENTMAIL_FAC] == NULL);

  _maillage_elt_fam_fusionne(&(maillage->elt_fam[ECS_ENTMAIL_FAC]),
                             nbr_fac_old,
                             nbr_elt_new,
                             vect_transf);

  _maillage_renum_connect(maillage,
                          ECS_ENTMAIL_FAC,
                          vect_transf);


  ecs_table__renumerote(maillage->table_def[ECS_ENTMAIL_CEL],
                        vect_transf,
                        signe_elt);

  ECS_FREE(signe_elt.val);
  ECS_FREE(vect_transf.val);


  _maillage__nettoie_descend(maillage);
}
