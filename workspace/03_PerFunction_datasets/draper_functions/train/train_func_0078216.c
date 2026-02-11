p_fmac_steps_spinbutton_cb(GtkObject *obj, GapStbPropWidget *pw)
{
  gint32 l_val;
  if(pw)
  {
    l_val = (GTK_ADJUSTMENT(pw->pw_spinbutton_fmac_steps_adj)->value);
    if(pw->stb_elem_refptr)
    {
      if(pw->stb_elem_refptr->fmac_total_steps != l_val)
      {
        p_pw_push_undo_and_set_unsaved_changes(pw);
        pw->stb_elem_refptr->fmac_total_steps = l_val;

        p_pw_check_fmac_sensitivity(pw);

      }
    }
  }
}
