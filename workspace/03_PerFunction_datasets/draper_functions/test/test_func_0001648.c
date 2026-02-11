p_update_ainfo_dependent_widgets(GapPlayerMainGlobalParams *gpp)
{
  gdouble l_lower;
  gdouble l_upper;
  gdouble l_value;

  if(gpp == NULL) { return; }
  if(gpp->ainfo_ptr == NULL) { return; }

  l_lower = (gdouble)gpp->ainfo_ptr->first_frame_nr;
  l_upper = (gdouble)gpp->ainfo_ptr->last_frame_nr;


  GTK_ADJUSTMENT(gpp->from_spinbutton_adj)->lower = l_lower;
  GTK_ADJUSTMENT(gpp->from_spinbutton_adj)->upper = l_upper;
  GTK_ADJUSTMENT(gpp->from_spinbutton_adj)->value = CLAMP(GTK_ADJUSTMENT(gpp->from_spinbutton_adj)->value
                                                         ,l_lower, l_upper);
  gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->from_spinbutton_adj)
                            , (gfloat)CLAMP(GTK_ADJUSTMENT(gpp->from_spinbutton_adj)->value, l_lower, l_upper)
                            );

  GTK_ADJUSTMENT(gpp->to_spinbutton_adj)->lower = l_lower;
  GTK_ADJUSTMENT(gpp->to_spinbutton_adj)->upper = l_upper;
  gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->to_spinbutton_adj)
                          , (gfloat) CLAMP(GTK_ADJUSTMENT(gpp->to_spinbutton_adj)->value, l_lower, l_upper)
                          );

  l_value = CLAMP(GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj)->value, l_lower, l_upper);

  if(gap_debug)
  {
    printf("## tmp p_update_ainfo_dependent_widgets adj l_value:%.2f  l_lower:%.2f  l_upper:%.2f\n"
        ,(float)l_value
        ,(float)l_lower
        ,(float)l_upper
        );
  }

  GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj)->lower = l_lower;
  GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj)->upper = l_upper;
  gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->framenr_spinbutton_adj), l_value);

}
