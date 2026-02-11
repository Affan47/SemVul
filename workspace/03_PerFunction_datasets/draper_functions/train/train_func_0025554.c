gms_fatal (const char *string)
{


  if (!gms_main_window)
    {
      fprintf (stderr, "\n\nINTERNAL ERROR: %s\n", string);

      fprintf (stderr, "\nPlease record the details of this error, try to"
                       " note down everything you did to cause it, and email"
                       " this information to simon_baldwin@yahoo.com.\n\n");
      return;
    }


  glk_cancel_line_event (gms_main_window, NULL);
  glk_cancel_char_event (gms_main_window);
  if (gms_hint_menu_window)
    {
      glk_cancel_char_event (gms_hint_menu_window);
      glk_window_close (gms_hint_menu_window, NULL);
    }
  if (gms_hint_text_window)
    {
      glk_cancel_char_event (gms_hint_text_window);
      glk_window_close (gms_hint_text_window, NULL);
    }


  glk_set_window (gms_main_window);
  glk_set_style (style_Normal);
  glk_put_string ("\n\nINTERNAL ERROR: ");
  glk_put_string ((char *) string);

  glk_put_string ("\n\nPlease record the details of this error, try to"
                  " note down everything you did to cause it, and email"
                  " this information to simon_baldwin@yahoo.com.\n\n");
}
