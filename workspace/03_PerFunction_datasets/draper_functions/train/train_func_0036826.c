meta_frame_style_validate (MetaFrameStyle    *style,
                           guint              current_theme_version,
                           GError           **error)
{
  int i, j;

  g_return_val_if_fail (style != NULL, FALSE);
  g_return_val_if_fail (style->layout != NULL, FALSE);

  for (i = 0; i < META_BUTTON_TYPE_LAST; i++)
    {

      if (i >= META_BUTTON_TYPE_CLOSE)
        {
          for (j = 0; j < META_BUTTON_STATE_LAST; j++)
            {
              if (get_button (style, i, j) == NULL &&
                  meta_theme_earliest_version_with_button (i) <= current_theme_version
                  )
                {
                  g_set_error (error, META_THEME_ERROR,
                               META_THEME_ERROR_FAILED,
                               _("<button function=\"%s\" state=\"%s\" draw_ops=\"whatever\"/> must be specified for this frame style"),
                               meta_button_type_to_string (i),
                               meta_button_state_to_string (j));
                  return FALSE;
                }
            }
        }
    }

  return TRUE;
}
