draw_status_all(void)
{


  {
    SDL_Rect src = {0, 0, 640, 80}, dst = {0, 400};
    gfx_blit_nocolorkey(GFX_k[seq[180].frame[3]].k, &src, GFX_lpDDSTwo, &dst);
  }


  {
    SDL_Rect src = {0, 0, 20, 400}, dst1 = {0, 0}, dst2 = {620, 0};
    gfx_blit_nocolorkey(GFX_k[seq[180].frame[1]].k, &src, GFX_lpDDSTwo, &dst1);
    gfx_blit_nocolorkey(GFX_k[seq[180].frame[2]].k, &src, GFX_lpDDSTwo, &dst2);
  }

  fraise = next_raise();
  if (*pexper < fraise)
    fexp = *pexper;
  else
    fexp = fraise - 1;
  fstrength = *pstrength;
  fmagic = *pmagic;
  fgold = *pgold;
  fdefense = *pdefense;
  last_magic_draw = 0;
  draw_exp();
  draw_health();
  draw_strength();
  draw_defense();
  draw_magic();
  draw_gold();
  draw_level();
  draw_icons();
  if (*pmagic_cost > 0 && *pmagic_level > 0)
    draw_mlevel(*pmagic_level * 100 / *pmagic_cost);
}
