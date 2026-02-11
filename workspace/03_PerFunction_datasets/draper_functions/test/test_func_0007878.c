lib_cmd_interrogation (sc_gameref_t game)
{
  const sc_filterref_t filter = gs_get_filter (game);
  const sc_char *string = NULL;

  switch (sc_randomint (1, 17))
    {
    case 1:
      string = "Why do you want to know?\n";
      break;
    case 2:
      string = "Interesting question.\n";
      break;
    case 3:
      string = "Let me think about that one...\n";
      break;
    case 4:
      string = "I haven't a clue!\n";
      break;
    case 5:
      string = "All these questions are hurting my head.\n";
      break;
    case 6:
      string = "I'm not going to tell you.\n";
      break;
    case 7:
      string = "Someday I'll know the answer to that one.\n";
      break;
    case 8:
      string = "I could tell you, but then I'd have to kill you.\n";
      break;
    case 9:
      string = "Ha, as if I'd tell you!\n";
      break;
    case 10:
      string = "Ask me again later.\n";
      break;
    case 11:
      string = "I don't know - could you ask anyone else?\n";
      break;
    case 12:
      string = "Err, yes?!?\n";
      break;
    case 13:
      string = "Let me just check my memory banks...\n";
      break;
    case 14:
      string = "Because that's just the way it is.\n";
      break;
    case 15:
      string = "Do I ask you all sorts of awkward questions?\n";
      break;
    case 16:
      string = "Questions, questions...\n";
      break;
    default:
      string = "Who cares.\n";
      break;
    }

  pf_buffer_string (filter, string);
  return TRUE;
}
