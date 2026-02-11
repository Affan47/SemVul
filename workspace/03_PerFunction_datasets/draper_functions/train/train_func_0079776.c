p_radio_flip_update(GapStbPropWidget *pw, gint32 flip_request)
{
  if(pw)
  {
    pw->flip_request = flip_request;
    if(pw->stb_elem_refptr)
    {
      p_pw_push_undo_and_set_unsaved_changes(pw);
      pw->stb_elem_refptr->flip_request = pw->flip_request;
      p_pw_update_properties(pw);
      p_pw_propagate_mask_attribute_changes(pw);
    }
  }
}
