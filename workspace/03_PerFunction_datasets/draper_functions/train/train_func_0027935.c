os_display_hints (sc_game game)
{
  sc_game_hint hint;
  sc_int refused;


  refused = 0;
  for (hint = sc_get_first_game_hint (game);
       hint; hint = sc_get_next_game_hint (game, hint))
    {
      const sc_char *hint_question, *hint_text;


      if (refused >= GSC_HINT_REFUSAL_LIMIT)
        {
          if (!os_confirm (GSC_CONF_CONTINUE_HINTS))
            break;
          refused = 0;
        }


      hint_question = sc_get_game_hint_question (game, hint);
      gsc_normal_char ('\n');
      gsc_standout_string (hint_question);
      gsc_normal_char ('\n');


      hint_text = sc_get_game_subtle_hint (game, hint);
      if (hint_text)
        {
          if (!os_confirm (GSC_CONF_SUBTLE_HINT))
            {
              refused++;
              continue;
            }
          gsc_normal_char ('\n');
          gsc_standout_string (hint_text);
          gsc_normal_string ("\n\n");
        }


      hint_text = sc_get_game_unsubtle_hint (game, hint);
      if (hint_text)
        {
          if (!os_confirm (GSC_CONF_UNSUBTLE_HINT))
            {
              refused++;
              continue;
            }
          gsc_normal_char ('\n');
          gsc_standout_string (hint_text);
          gsc_normal_string ("\n\n");
        }
    }
}
