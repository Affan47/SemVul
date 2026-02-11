check_state  (MetaFrameStyleSet *style_set,
              MetaFrameState     state,
              GError           **error)
{
  int i;

  for (i = 0; i < META_FRAME_FOCUS_LAST; i++)
    {
      if (get_style (style_set, state,
                     META_FRAME_RESIZE_NONE, i) == NULL)
        {


          g_set_error (error, META_THEME_ERROR,
                       META_THEME_ERROR_FAILED,
                       _("Missing <frame state=\"%s\" resize=\"%s\" focus=\"%s\" style=\"whatever\"/>"),
                       meta_frame_state_to_string (state),
                       meta_frame_resize_to_string (META_FRAME_RESIZE_NONE),
                       meta_frame_focus_to_string (i));
          return FALSE;
        }
    }

  return TRUE;
}
