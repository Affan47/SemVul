gsc_get_ending_option (void)
{
  sc_char response;


  gsc_reset_glk_style ();
  gsc_status_notify ();


  glk_put_string ("\nWould you like to RESTART, UNDO a turn, or QUIT? ");


  do
    {
      event_t event;

      do
        {
          glk_request_char_event (gsc_main_window);
          gsc_event_wait (evtype_CharInput, &event);
        }
      while (event.val1 > UCHAR_MAX);
      response = glk_char_to_upper (event.val1);
    }
  while (response != 'R' && response != 'U' && response != 'Q');


  glk_set_style (style_Input);
  switch (response)
    {
    case 'R':
      glk_put_string ("Restart");
      break;
    case 'U':
      glk_put_string ("Undo");
      break;
    case 'Q':
      glk_put_string ("Quit");
      break;
    default:
      gsc_fatal ("GLK: Invalid response encountered");
      glk_exit ();
    }
  glk_set_style (style_Normal);
  glk_put_char ('\n');


  switch (response)
    {
    case 'R':
      return GAME_RESTART;
    case 'U':
      return GAME_UNDO;
    case 'Q':
      return GAME_QUIT;
    default:
      gsc_fatal ("GLK: Invalid response encountered");
      glk_exit ();
    }


  return GAME_QUIT;
}
