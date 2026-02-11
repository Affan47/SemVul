p_init_widget_values(GapGveAviGlobalParams *gpp)
{
  GapGveAviValues *epp;

  epp = &gpp->evl;
  if(epp == NULL)
  {
    return;
  }


  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->jpg_quality_spinbutton_adj)
                         , (gfloat)epp->jpeg_quality);

  gpp->xvid_kbitrate = epp->xvid.rc_bitrate / 1000;

  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_rc_kbitrate_spinbutton_adj)
                         , (gfloat)gpp->xvid_kbitrate);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_rc_reaction_delay_spinbutton_adj)
                         , (gfloat)epp->xvid.rc_reaction_delay_factor);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_rc_avg_period_spinbutton_adj)
                         , (gfloat)epp->xvid.rc_averaging_period);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_rc_buffer_spinbutton_adj)
                         , (gfloat)epp->xvid.rc_buffer);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_max_quantizer_spinbutton_adj)
                         , (gfloat)epp->xvid.max_quantizer);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_min_quantizer_spinbutton_adj)
                         , (gfloat)epp->xvid.min_quantizer);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_max_key_interval_spinbutton_adj)
                         , (gfloat)epp->xvid.max_key_interval);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gpp->xvid_quality_spinbutton_adj)
                         , (gfloat)epp->xvid.quality_preset);


  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gpp->jpg_dont_recode_checkbutton)
                               , epp->jpeg_dont_recode_frames);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gpp->jpg_interlace_checkbutton)
                               , epp->jpeg_interlaced);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gpp->jpg_odd_first_checkbutton)
                               , epp->jpeg_odd_even);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gpp->app0_checkbutton)
                               , epp->APP0_marker);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gpp->raw_vflip_checkbutton)
                               , epp->raw_vflip);


  {
    gint l_idx;
    l_idx = p_get_initial_video_codec_idx(gpp);
    gimp_int_combo_box_set_active (GIMP_INT_COMBO_BOX (gpp->combo_codec), l_idx);
    p_set_codec_dependent_wgt_senistive(gpp, l_idx);
  }
}
