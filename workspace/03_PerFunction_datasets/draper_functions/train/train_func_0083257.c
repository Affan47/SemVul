on_restore_equal_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int lp,i=0;
  for(lp=1;lp<=MAX_WINS; lp++)
    if(
#ifndef IS_PLYMORPH
        !sp->im_widget_is_difference_mesh[lp] &&
#endif
	sp->im_widget[lp] != NULL ) i++;
  for(lp=1;lp<=MAX_WINS; lp++)
    if(
#ifndef IS_PLYMORPH
       !sp->im_widget_is_difference_mesh[lp] &&
#endif
       sp->im_widget[lp] != NULL)
      sp->mf.im_warp_factor[lp]=sp->mf.im_dissolve_factor[lp]=1./(double)i;
  redraw_spins(-3);
}
