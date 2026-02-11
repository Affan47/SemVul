_maillage__compte_typ_fac(const ecs_tab_int_t  *typ_fac,
                          size_t               *nbr_fac_erreur,
                          size_t               *nbr_fac_interne,
                          size_t               *nbr_fac_de_bord,
                          size_t               *nbr_fac_isolee)
{
  size_t  ifac;


  assert(typ_fac != NULL);


  *nbr_fac_erreur  = 0;
  *nbr_fac_interne = 0;
  *nbr_fac_de_bord = 0;
  *nbr_fac_isolee  = 0;


  for (ifac = 0; ifac < typ_fac->nbr; ifac++) {

    switch(typ_fac->val[ifac]) {

    case 0:
      *nbr_fac_isolee += 1;
      break;

    case 1:
    case 2:
      *nbr_fac_de_bord += 1;
      break;

    case 3:
      *nbr_fac_interne += 1;
      break;

    default:
      *nbr_fac_erreur += 1;

    }
  }

  if (*nbr_fac_erreur != 0) {
    ecs_warn();
    printf(_("There are %lu faces of which one same side belongs\n"
             "to at least 2 cells --> bad connectivity."),
           (unsigned long)(*nbr_fac_erreur));
  }

  if (*nbr_fac_isolee != 0) {
    ecs_warn();
    printf(_("There is/are %lu isolated face(s)\n"),
           (unsigned long)(*nbr_fac_isolee));
  }
}
