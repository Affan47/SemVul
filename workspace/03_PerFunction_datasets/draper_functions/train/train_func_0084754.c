on_framenr_button_clicked             (GtkButton       *button,
                                       GdkEventButton  *bevent,
                                       GapPlayerMainGlobalParams *gpp)
{
   GimpParam       *return_vals;
   int              nreturn_vals;
   gint             button_type;
   gint32           dummy_layer_id;


  if(gpp == NULL)
  {
    return;
  }

  p_stop_playback(gpp);

  if(button)
  {
    button_type = (gint) g_object_get_data (G_OBJECT (button), KEY_FRAMENR_BUTTON_TYPE);
  }
  else
  {
    button_type = FRAMENR_BUTTON_BEGIN;
  }

  if(bevent)
  {
    if (!(bevent->state & GDK_SHIFT_MASK))
    {

      if(button_type == FRAMENR_BUTTON_END)
      {

        gpp->end_frame = gpp->play_current_framenr;
        gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->to_spinbutton_adj)
                                  , (gfloat)gpp->play_current_framenr
                                  );
        if(gpp->end_frame < gpp->begin_frame)
        {
          gpp->begin_frame = gpp->end_frame;
          gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->from_spinbutton_adj)
                                  , (gfloat)gpp->begin_frame
                                  );
        }
        return;
      }


      gpp->begin_frame = gpp->play_current_framenr;
      gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->from_spinbutton_adj)
                              , (gfloat)gpp->play_current_framenr
                              );
      if(gpp->begin_frame > gpp->end_frame)
      {
        gpp->end_frame = gpp->begin_frame;
        gtk_adjustment_set_value( GTK_ADJUSTMENT(gpp->to_spinbutton_adj)
                                , (gfloat)gpp->end_frame
                                );
      }
      return;

    }
  }

  if((gpp->stb_ptr)
  || (gpp->image_id < 0))
  {

    return;
  }


  dummy_layer_id = gap_image_get_any_layer(gpp->image_id);
  return_vals = gimp_run_procedure ("plug_in_gap_goto",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32,    GIMP_RUN_NONINTERACTIVE,
                                    GIMP_PDB_IMAGE,    gpp->image_id,
                                    GIMP_PDB_DRAWABLE, dummy_layer_id,
                                    GIMP_PDB_INT32,    gpp->play_current_framenr,
                                    GIMP_PDB_END);

  if(return_vals)
  {
    if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
       p_reload_ainfo_ptr(gpp, return_vals[1].data.d_image);
       p_update_ainfo_dependent_widgets(gpp);
       gimp_displays_flush();
    }

    gimp_destroy_params(return_vals, nreturn_vals);
  }


}
