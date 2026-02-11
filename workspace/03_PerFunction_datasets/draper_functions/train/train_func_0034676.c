handle_depth_halftone (Epson_Scanner * s, SANE_Bool * reload)


{
  int hti = s->val[OPT_HALFTONE].w;
  int mdi = s->val[OPT_MODE].w;
  SANE_Bool aas = SANE_FALSE;
  SANE_Bool thresh = SANE_FALSE;

  if (!s->hw->cmd->control_auto_area_segmentation)
    return;

  if (mode_params[mdi].depth == 1)
  {
    if (halftone_params[hti] != HALFTONE_TET)
    {
      aas = SANE_TRUE;
    }
    if (halftone_params[hti] == HALFTONE_NONE)
    {
      thresh = SANE_TRUE;
    }
  }
  setOptionState (s, aas, OPT_AAS, reload);
  setOptionState (s, thresh, OPT_THRESHOLD, reload);
}
