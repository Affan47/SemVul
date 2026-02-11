beh_clrdepend (pt_fig)

struct befig *pt_fig;

  {
  struct berin *pt_rin;

  if (( pt_fig                           != NULL) &&
      ( pt_fig->ERRFLG                   == 0   ) &&
      ((pt_fig->FLAG   & BEH_FIG_DEPEND) != 0   )   )
    {
    pt_rin = pt_fig->BERIN;
    while (pt_rin != NULL)
      {
      freechain (pt_rin->OUT_REF);
      pt_rin->OUT_REF = NULL;

      freechain (pt_rin->AUX_REF);
      pt_rin->AUX_REF = NULL;

      freechain (pt_rin->REG_REF);
      pt_rin->REG_REF = NULL;

      freechain (pt_rin->BUS_REF);
      pt_rin->BUS_REF = NULL;

      freechain (pt_rin->BUX_REF);
      pt_rin->BUX_REF = NULL;

      freechain (pt_rin->MSG_REF);
      pt_rin->MSG_REF = NULL;

      freechain (pt_rin->DLY_REF);
      pt_rin->DLY_REF = NULL;

      pt_rin = pt_rin->NEXT;
      }

    pt_fig->FLAG ^= BEH_FIG_DEPEND;
    }
  }
