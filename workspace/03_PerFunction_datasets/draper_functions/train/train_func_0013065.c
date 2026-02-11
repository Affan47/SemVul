ecs_loc_pre_ens__ele_lin(int32_t     *connect_loc,
                         ecs_int_t    nbr_ele,
                         ecs_int_t    taille_ele,
                         ecs_int_t    taille_ele_lin)
{
  ecs_int_t    ielt;
  ecs_int_t    iloc;
  ecs_int_t    ipos_lin;
  ecs_int_t    ipos_ens;

  ipos_lin = 0;

  for (ielt = 0; ielt < nbr_ele; ielt++) {

    ipos_ens = ielt * taille_ele;

    for (iloc = 0; iloc < taille_ele_lin; iloc++)
      connect_loc[ipos_lin++] = connect_loc[ipos_ens++];

    ECS_REALLOC(connect_loc, ipos_lin, int32_t);
  }

  return connect_loc;
}
